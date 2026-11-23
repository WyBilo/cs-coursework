#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <fstream>
#include "StudentRecord.h"

class Database {
private:
    std::string fileName;
    int recordCount;

public:
    static const int RECORD_SIZE = 64;

    Database(const std::string& fileName);

    bool createEmpty();
    long appendRecord(const StudentRecord& record);
    bool readRecord(long position, StudentRecord& record);

    int getRecordCount() const;
    void setRecordCount(int count);

    std::string getFileName() const;
};

#endif