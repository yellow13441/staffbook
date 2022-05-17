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
#include <cstdlib>
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
using namespace std;

int GetInput() {
  int choice;    
  cin >> choice;
  return choice;
}

void DisplayMainMenu() {
  cout << "-------      Menu     -------\n";
  cout << "Please make your selection\n";
  cout << "1 - Add an employee\n";
  cout << "2 - Query an employee by ID\n";
  cout << "3 - List all employees\n";
  cout << "0 - Quit\n";
  cout << "Selection: ";
}

// This function fills in a Employee message based on user input.
void PromptForStaff(staffbook::Employee* employee) {
  cout << "Enter employee ID number: ";
  int id;
  cin >> id;
  employee->set_id(id);
  cin.ignore(256, '\n');

  cout << "Enter name: ";
  getline(cin, *employee->mutable_name());

  cout << "Enter age: ";
  int age;
  cin >> age;
  employee->set_age(age);
  cin.ignore(256, '\n');

  cout << "Enter gender (M or F): ";
  string gender;
  getline(cin, gender);
  if (gender == "M") {
    employee->set_gender(staffbook::Employee::MALE);
  } else if (gender == "F") {
    employee->set_gender(staffbook::Employee::FEMALE);
  } else {
    cout << "Unknown gender type. Using default: Other." << endl;
  }
  
  cout << "Enter email address (blank for none): ";
  string email;
  getline(cin, email);
  if (!email.empty()) {
    employee->set_email(email);
  }

  cout << "Enter phone number (blank for none): ";
  string phone;
  getline(cin, phone);
  if (!phone.empty()) {
    employee->set_phone(phone);
  }

  *employee->mutable_last_updated() = TimeUtil::SecondsToTimestamp(time(NULL));
}

class CURDClient {
 public:
  CURDClient(shared_ptr<Channel> channel)
      : stub_(CURD::NewStub(channel)) {
  }

  void AddEmployee() {
    google::protobuf::Empty empty;
    Employee employee;
    ClientContext context;

    cout << "Prompting for adding new employee" << endl;
    PromptForStaff(&employee);

    Status status = stub_->AddEmployee(&context, employee, &empty);;

    if (status.ok()) {
      cout << "AddEmployee rpc successed." << endl;
    } else {
      cout << "AddEmployee rpc failed." << endl;
      cout << status.error_code() << ": " << status.error_message() << endl;
    }
  }
  
  void ListEmployees() {
    const google::protobuf::Empty empty;
    staffbook::StaffBook staff_book;
    Employee employee;
    ClientContext context;

    cout << "Looking for all employees" << endl;
    Status status = stub_->ListEmployees(&context, empty, &staff_book);;

    if (status.ok()) {
      cout << "ListEmployees rpc succeeded." << endl;
      for (int i = 0; i < staff_book.employees_size(); i++) {
        const staffbook::Employee& employee = staff_book.employees(i);
        // staffbook::Employee& employee = staff_book.employees(i);
        cout << "Employee ID: " << employee.id() << endl;
        cout << "  Name: " << employee.name() << endl;
        cout << "  Age: " << employee.age() << endl;

        cout << "  Gender: ";
        switch (employee.gender()) {
          case staffbook::Employee::MALE:
            cout << "MALE" << endl;
            break;
          case staffbook::Employee::FEMALE:
            cout << "FEMALE" << endl;
            break;
          default:
            cout << "OTHERS" << endl;
            break;
        }

        if (employee.email() != "") {
          cout << "  E-mail address: " << employee.email() << endl;
        }

        if (employee.phone() != "") {
          cout << "  Phone number: " << employee.phone() << endl;
        }

        if (employee.has_last_updated()) {
          cout << "  Updated: " << TimeUtil::ToString(employee.last_updated()) << endl;
        }
      }
    } else {
      cout << "ListEmployees rpc failed." << endl;
      cout << status.error_code() << ": " << status.error_message() << endl;
    }
  }

 private:
  unique_ptr<CURD::Stub> stub_;
  // staffbook::StaffBook staff_book;
};

int main(int argc, char** argv) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  CURDClient book(
      grpc::CreateChannel("localhost:50051",
                          grpc::InsecureChannelCredentials()));

  int choice = 1;
  do {
    DisplayMainMenu();
    choice = GetInput();
    system("clear");
    switch(choice) {
      case 1:
        cout << "--------------  AddEmployee  --------------" << endl;
        book.AddEmployee();
        break;
      case 2: 
        cout << "-----------  QueryEmployeeByID  -----------" << endl;
        break;
      case 3: 
        cout << "-------------- ListEmployees --------------" << endl;
        book.ListEmployees();
        break;
      default: 
        break;
      }
  } while(choice);
  
  return 0;
}
