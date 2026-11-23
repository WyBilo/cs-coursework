#include "Database.h"

Database::Database(const std::string& fileName) {
    this->fileName = fileName;
    this->recordCount = 0;
}

bool Database::createEmpty() {
    std::ofstream outFile(fileName.c_str(), std::ios::binary | std::ios::trunc);

    if (!outFile) {
        return false;
    }

    outFile.close();
    recordCount = 0;
    return true;
}

long Database::appendRecord(const StudentRecord& record) {
    std::ofstream outFile(fileName.c_str(), std::ios::binary | std::ios::app);

    if (!outFile) {
        return -1;
    }

    long position = recordCount * RECORD_SIZE;

    std::string fixedRecord = record.toFixedLengthString();

    if ((int)fixedRecord.length() != RECORD_SIZE) {
        outFile.close();
        return -1;
    }

    outFile.write(fixedRecord.c_str(), RECORD_SIZE);
    outFile.close();

    recordCount++;

    return position;
}

bool Database::readRecord(long position, StudentRecord& record) {
    std::ifstream inFile(fileName.c_str(), std::ios::binary);

    if (!inFile) {
        return false;
    }

    inFile.seekg(position, std::ios::beg);

    char buffer[RECORD_SIZE + 1];
    inFile.read(buffer, RECORD_SIZE);

    if (!inFile) {
        inFile.close();
        return false;
    }

    buffer[RECORD_SIZE] = '\0';

    std::string fixedRecord(buffer, RECORD_SIZE);

    std::string id = fixedRecord.substr(0, 9);
    std::string lastName = fixedRecord.substr(9, 15);
    std::string firstName = fixedRecord.substr(24, 15);
    std::string year = fixedRecord.substr(39, 1);
    std::string major = fixedRecord.substr(40, 4);
    std::string email = fixedRecord.substr(44, 20);

    while (!id.empty() && id[id.length() - 1] == ' ') {
        id.erase(id.length() - 1);
    }

    while (!lastName.empty() && lastName[lastName.length() - 1] == ' ') {
        lastName.erase(lastName.length() - 1);
    }

    while (!firstName.empty() && firstName[firstName.length() - 1] == ' ') {
        firstName.erase(firstName.length() - 1);
    }

    while (!year.empty() && year[year.length() - 1] == ' ') {
        year.erase(year.length() - 1);
    }

    while (!major.empty() && major[major.length() - 1] == ' ') {
        major.erase(major.length() - 1);
    }

    while (!email.empty() && email[email.length() - 1] == ' ') {
        email.erase(email.length() - 1);
    }

    record = StudentRecord(id, lastName, firstName, year, major, email);

    inFile.close();
    return true;
}

int Database::getRecordCount() const {
    return recordCount;
}

void Database::setRecordCount(int count) {
    recordCount = count;
}

std::string Database::getFileName() const {
    return fileName;
}