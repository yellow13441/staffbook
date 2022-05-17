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
using namespace std;


class CURDImpl final : public CURD::Service {
 public:
  explicit CURDImpl(const string& db) {
    // Read the existing staff book.
    cout << db << endl;
    DBPATH = db;
    fstream input(db, ios::in | ios::binary);
    if (!staff_book.ParseFromIstream(&input)) {
      cerr << "Error parsing the staffbook db" << endl;
    }
  }

  Status AddEmployee(ServerContext* context, const staffbook::Employee* employee_request, google::protobuf::Empty* empty) {
    cout << "Received a AddEmployee RPC at " << TimeUtil::ToString(TimeUtil::SecondsToTimestamp(time(NULL))) << endl;
    
    // Add an staff.
    staffbook::Employee* employee_add = staff_book.add_employees();
    employee_add->set_id(employee_request->id()); 
    employee_add->set_name(employee_request->name()); 
    employee_add->set_age(employee_request->age()); 
    employee_add->set_gender(employee_request->gender()); 
    employee_add->set_email(employee_request->email()); 
    employee_add->set_phone(employee_request->phone()); 
    *employee_add->mutable_last_updated() = employee_request->last_updated(); 

    // Write the new staff book back to disk.
    fstream output(DBPATH, ios::out | ios::trunc | ios::binary);
    if (!staff_book.SerializeToOstream(&output)) {
      cerr << "Failed to write staff book." << endl;
    }

    return Status::OK;
  }

  Status ListEmployees(ServerContext* context, const google::protobuf::Empty* empty, staffbook::StaffBook* staff_book_reply) {
    cout << "Received a ListEmployees RPC at " << TimeUtil::ToString(TimeUtil::SecondsToTimestamp(time(NULL))) << endl;

    for (int i = 0; i < staff_book.employees_size(); i++) {
      const staffbook::Employee& employee = staff_book.employees(i);
      staffbook::Employee* employee_reply = staff_book_reply->add_employees();
      employee_reply->set_id(employee.id()); 
      employee_reply->set_name(employee.name()); 
      employee_reply->set_age(employee.age()); 
      employee_reply->set_gender(employee.gender()); 
      employee_reply->set_email(employee.email()); 
      employee_reply->set_phone(employee.phone()); 
      *employee_reply->mutable_last_updated() = employee.last_updated(); 
    }

    return Status::OK;
  }

  Status QueryEmployeeByID(ServerContext* context, const staffbook::IDRequest* id_request, staffbook::Employee* employee_reply) {
    cout << "Received a QueryEmployeeByID RPC at " << TimeUtil::ToString(TimeUtil::SecondsToTimestamp(time(NULL))) << endl;

    int id = id_request->id();
    for (int i = 0; i < staff_book.employees_size(); i++) {
      const staffbook::Employee& employee = staff_book.employees(i);
      // cout << i << ": " << employee.id() << endl;
      if (employee.id() == id) {
        employee_reply->set_id(employee.id()); 
        employee_reply->set_name(employee.name()); 
        employee_reply->set_age(employee.age()); 
        employee_reply->set_gender(employee.gender()); 
        employee_reply->set_email(employee.email()); 
        employee_reply->set_phone(employee.phone()); 
        *employee_reply->mutable_last_updated() = employee.last_updated(); 
        // cout << "found" << endl;
        // return Status::OK;
        break;
      }
    }
    // todo
    // Error Handling: What if employee specified ID not found?
    // https://cloud.google.com/apis/design/errors#error_model
    // return Status::error(2, "Invalid ID, check your input.");
    return Status::OK;
  }

 private:
  staffbook::StaffBook staff_book;
  mutex mu_;
  string DBPATH;
};

void RunServer(const string& db_path) {
  string server_address("0.0.0.0:50051");
  CURDImpl service(db_path);

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  unique_ptr<Server> server(builder.BuildAndStart());
  cout << "Server listening on " << server_address << endl;
  server->Wait();
}

int main(int argc, char** argv) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    // Expect only arg: --db_path=path/to/staffbook.data
    cerr << "Usage:  " << argv[0] << " STAFF_BOOK_FILE" << endl;
    return -1;
  }
  string db(argv[1]);
  RunServer(db);

  return 0;
}
