// See README.txt for information and build instructions.

#include <ctime>
#include <fstream>
#include <google/protobuf/util/time_util.h>
#include <iostream>
#include <string>

#include "staffbook.pb.h"

using namespace std;

using google::protobuf::util::TimeUtil;

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

// Main function:  Reads the entire staff book from a file,
//   adds one employee based on user input, then writes it back out to the same
//   file.
int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " STAFF_BOOK_FILE" << endl;
    return -1;
  }

  staffbook::StaffBook staff_book;

  {
    // Read the existing staff book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!input) {
      cout << argv[1] << ": File not found.  Creating a new file." << endl;
    } else if (!staff_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse staff book." << endl;
      return -1;
    }
  }

  // Add an staff.
  PromptForStaff(staff_book.add_employees());

  {
    // Write the new staff book back to disk.
    fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    if (!staff_book.SerializeToOstream(&output)) {
      cerr << "Failed to write staff book." << endl;
      return -1;
    }
  }

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
