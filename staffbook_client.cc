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

#include <chrono>
#include <fstream>
#include <iostream>
#include <google/protobuf/util/time_util.h>
#include <memory>
#include <random>
#include <string>
#include <thread>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#ifdef BAZEL_BUILD
#include "examples/protos/staffbook.grpc.pb.h"
#else
#include "staffbook.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using staffbook::Employee;
using staffbook::StaffBook;
using staffbook::CURD;
using google::protobuf::util::TimeUtil;
// todo
// Employee MakeEmployee(int id, long longitude) {
//   Employee e;
//   e.set_latitude(latitude);
//   e.set_longitude(longitude);
//   return p;
// }


class CURDClient {
 public:
  CURDClient(std::shared_ptr<Channel> channel)
      : stub_(CURD::NewStub(channel)) {
    // // Read the existing staff book.
    // std::cout << db << std::endl;

    // std::fstream input(db, std::ios::in | std::ios::binary);
    // if (!staff_book.ParseFromIstream(&input)) {
    //   std::cerr << "Error parsing the staffbook db" << std::endl;
    //   // return -1;
    // }
  }

  void ListEmployees() {
    google::protobuf::Empty empty;
    staffbook::StaffBook staff_book;
    Employee employee;
    ClientContext context;

    

    // std::unique_ptr<ClientReader<Employee> > reader(
    //     stub_->ListEmployees(&context, empty, &staff_book));
    // while (reader->Read(&employee)) {
    //   std::cout << "Employee ID: " << employee.id() << std::endl;
    //   std::cout << "  Name: " << employee.name() << std::endl;
    //   std::cout << "  Age: " << employee.age() << std::endl;

    //   std::cout << "  Gender: ";
    //   switch (employee.gender()) {
    //     case staffbook::Employee::MALE:
    //       std::cout << "MALE" << std::endl;
    //       break;
    //     case staffbook::Employee::FEMALE:
    //       std::cout << "FEMALE" << std::endl;
    //       break;
    //     default:
    //       std::cout << "OTHERS" << std::endl;
    //       break;
    //   }

    //   if (employee.email() != "") {
    //     std::cout << "  E-mail address: " << employee.email() << std::endl;
    //   }

    //   if (employee.phone() != "") {
    //     std::cout << "  Phone number: " << employee.phone() << std::endl;
    //   }

    //   if (employee.has_last_updated()) {
    //     std::cout << "  Updated: " << TimeUtil::ToString(employee.last_updated()) << std::endl;
    //   }
    // }

    std::cout << "Looking for all employees" << std::endl;
    Status status = stub_->ListEmployees(&context, empty, &staff_book);

    for (int i = 0; i < staff_book.employees_size(); i++) {
    const staffbook::Employee& employee = staff_book.employees(i);
    std::cout << "Employee ID: " << employee.id() << std::endl;
      std::cout << "  Name: " << employee.name() << std::endl;
      std::cout << "  Age: " << employee.age() << std::endl;

      std::cout << "  Gender: ";
      switch (employee.gender()) {
        case staffbook::Employee::MALE:
          std::cout << "MALE" << std::endl;
          break;
        case staffbook::Employee::FEMALE:
          std::cout << "FEMALE" << std::endl;
          break;
        default:
          std::cout << "OTHERS" << std::endl;
          break;
      }

      if (employee.email() != "") {
        std::cout << "  E-mail address: " << employee.email() << std::endl;
      }

      if (employee.phone() != "") {
        std::cout << "  Phone number: " << employee.phone() << std::endl;
      }

      if (employee.has_last_updated()) {
        std::cout << "  Updated: " << TimeUtil::ToString(employee.last_updated()) << std::endl;
      }
    }

    if (status.ok()) {
      std::cout << "ListEmployees rpc succeeded." << std::endl;
    } else {
      std::cout << "ListEmployees rpc failed." << std::endl;
    }
  }

 private:
  std::unique_ptr<CURD::Stub> stub_;
  // staffbook::StaffBook staff_book;
};

int main(int argc, char** argv) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  // if (argc != 2) {
  //   // Expect only arg: --db_path=path/to/staffbook.data
  //   std::cerr << "Usage:  " << argv[0] << " STAFF_BOOK_FILE" << std::endl;
  //   return -1;
  // }
  // std::string db(argv[1]);

  CURDClient book(
      grpc::CreateChannel("localhost:50051",
                          grpc::InsecureChannelCredentials()));

  std::cout << "-------------- ListEmployees --------------" << std::endl;
  book.ListEmployees();
  
  return 0;
}
