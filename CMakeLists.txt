# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# cmake build file for C++ staffbook example.
# Assumes protobuf and gRPC have been installed using cmake.
# See cmake_externalproject/CMakeLists.txt for all-in-one cmake build
# that automatically builds all the dependencies before building staffbook.

cmake_minimum_required(VERSION 3.5.1)

project(StaffBook C CXX)

include(common.cmake)

# Proto file
get_filename_component(sb_proto "staffbook.proto" ABSOLUTE)
get_filename_component(sb_proto_path "${sb_proto}" PATH)

# Generated sources
set(sb_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/staffbook.pb.cc")
set(sb_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/staffbook.pb.h")
set(sb_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/staffbook.grpc.pb.cc")
set(sb_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/staffbook.grpc.pb.h")
add_custom_command(
      OUTPUT "${sb_proto_srcs}" "${sb_proto_hdrs}" "${sb_grpc_srcs}" "${sb_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${sb_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${sb_proto}"
      DEPENDS "${sb_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# sb_grpc_proto
add_library(sb_grpc_proto
  ${sb_grpc_srcs}
  ${sb_grpc_hdrs}
  ${sb_proto_srcs}
  ${sb_proto_hdrs})
target_link_libraries(sb_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Targets greeter_[async_](client|server)
foreach(_target
  add_employee list_employees query_employee staffbook_server)
  add_executable(${_target} "${_target}.cc")
  target_link_libraries(${_target}
    sb_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})
endforeach()
