/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <algorithm>
#include <chrono>
#include <cmath>
#include <google/protobuf/util/time_util.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#ifdef BAZEL_BUILD
#include "examples/protos/staffbook.grpc.pb.h"
#else
#include "staffbook.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
// using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
// using routeguide::Feature;
// using routeguide::Point;
// using routeguide::Rectangle;
// using routeguide::RouteGuide;
// using routeguide::RouteNote;
// using routeguide::RouteSummary;
using staffbook::CURD;
using std::chrono::system_clock;
using google::protobuf::util::TimeUtil;


class CURDImpl final : public CURD::Service {
 public:
  explicit CURDImpl(const std::string& db) {
    // Read the existing staff book.
    std::cout << db << std::endl;

    std::fstream input(db, std::ios::in | std::ios::binary);
    if (!staff_book.ParseFromIstream(&input)) {
      std::cerr << "Error parsing the staffbook db" << std::endl;
      // return -1;
    }
  }

  Status ListEmployees(ServerContext* context, staffbook::StaffBook* staff_book_reply) {
    staff_book_reply = &staff_book;
    // google::protobuf::Empty* empty;
    // for (int i = 0; i < staff_book.employees_size(); i++) {
    //   const staffbook::Employee& employee = staff_book.employees(i);
    //   staff_book_reply->add_employees(context, &employee, empty);
    // // ::grpc::Status AddEmployee(::grpc::ServerContext* /*context*/, const ::staffbook::Employee* /*request*/, ::google::protobuf::Empty* /*response*/) override {
    // }
    return Status::OK;
  }

 private:
  staffbook::StaffBook staff_book;
  std::mutex mu_;
};

void RunServer(const std::string& db_path) {
  std::string server_address("0.0.0.0:50051");
  CURDImpl service(db_path);

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    // Expect only arg: --db_path=path/to/staffbook.data
    std::cerr << "Usage:  " << argv[0] << " STAFF_BOOK_FILE" << std::endl;
    return -1;
  }
  std::string db(argv[1]);
  RunServer(db);

  return 0;
}
