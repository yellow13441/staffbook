// See README.txt for information and build instructions.

#include <fstream>
#include <google/protobuf/util/time_util.h>
#include <iostream>
#include <string>

#include "staffbook.pb.h"

using namespace std;

using google::protobuf::util::TimeUtil;

// Iterates though all employees in the StaffBook and prints info about them.
void ListEmployees(const staffbook::StaffBook& staff_book) {
  for (int i = 0; i < staff_book.employees_size(); i++) {
    const staffbook::Employee& employee = staff_book.employees(i);

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
}

// Main function:  Reads the entire staff book from a file and prints all
//   the information inside.
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
    if (!staff_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse staff book." << endl;
      return -1;
    }
  }

  ListEmployees(staff_book);

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
