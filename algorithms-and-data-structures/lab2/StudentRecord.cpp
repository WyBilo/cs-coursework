#include "StudentRecord.h"

StudentRecord::StudentRecord() {
    id = "";
    lastName = "";
    firstName = "";
    year = "";
    major = "";
    email = "";
}

StudentRecord::StudentRecord(
    const std::string& id,
    const std::string& lastName,
    const std::string& firstName,
    const std::string& year,
    const std::string& major,
    const std::string& email
) {
    this->id = id;
    this->lastName = lastName;
    this->firstName = firstName;
    this->year = year;
    this->major = major;
    this->email = email;
}

std::string StudentRecord::padRight(const std::string& value, int width) const {
    if ((int)value.length() >= width) {
        return value.substr(0, width);
    }

    return value + std::string(width - value.length(), ' ');
}

bool StudentRecord::parseLine(const std::string& line, StudentRecord& record) {
    std::stringstream ss(line);

    std::string id;
    std::string lastName;
    std::string firstName;
    std::string year;
    std::string major;
    std::string email;

    if (!(ss >> id >> lastName >> firstName >> year >> major >> email)) {
        return false;
    }

    record = StudentRecord(id, lastName, firstName, year, major, email);
    return true;
}

std::string StudentRecord::toFixedLengthString() const {
    std::string fixedRecord = "";

    fixedRecord += padRight(id, 9);
    fixedRecord += padRight(lastName, 15);
    fixedRecord += padRight(firstName, 15);
    fixedRecord += padRight(year, 1);
    fixedRecord += padRight(major, 4);
    fixedRecord += padRight(email, 20);

    return fixedRecord;
}

std::string StudentRecord::toPrintableString() const {
    std::string printable = "";

    printable += padRight(id, 9);
    printable += " ";
    printable += padRight(lastName, 15);
    printable += " ";
    printable += padRight(firstName, 15);
    printable += " ";
    printable += padRight(year, 1);
    printable += " ";
    printable += padRight(major, 4);
    printable += " ";
    printable += padRight(email, 20);

    return printable;
}

std::string StudentRecord::getId() const {
    return id;
}

std::string StudentRecord::getLastName() const {
    return lastName;
}