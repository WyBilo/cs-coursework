#ifndef STUDENT_RECORD_H
#define STUDENT_RECORD_H

#include <string>
#include <sstream>
#include <iomanip>

class StudentRecord {
private:
    std::string id;
    std::string lastName;
    std::string firstName;
    std::string year;
    std::string major;
    std::string email;

    std::string padRight(const std::string& value, int width) const;

public:
    StudentRecord();

    StudentRecord(
        const std::string& id,
        const std::string& lastName,
        const std::string& firstName,
        const std::string& year,
        const std::string& major,
        const std::string& email
    );

    static bool parseLine(const std::string& line, StudentRecord& record);

    std::string toFixedLengthString() const;
    std::string toPrintableString() const;

    std::string getId() const;
    std::string getLastName() const;
};

#endif