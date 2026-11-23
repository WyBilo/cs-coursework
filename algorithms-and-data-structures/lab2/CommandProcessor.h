#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <string>
#include <fstream>
#include "StudentRecord.h"
#include "Database.h"
#include "BTree.h"

class CommandProcessor {
private:
    std::string dataFileName;
    std::string baseName;
    std::string commandFileName;
    std::string outputFileName;

    int order;

    Database* database;
    BTree* idIndex;
    BTree* nameIndex;

    void writeStatus(std::ofstream& outFile);
    void writeRecord(std::ofstream& outFile, long position);

    bool buildInitialFiles();

    void processFindId(std::ofstream& outFile,
                    const std::string& id);

    void processFindName(std::ofstream& outFile,
                        const std::string& lastName);

    void processAdd(std::ofstream& outFile,
                    const std::string& id,
                    const std::string& lastName,
                    const std::string& firstName,
                    const std::string& year,
                    const std::string& major,
                    const std::string& email);

    void processDump(std::ofstream& outFile,
                    const std::string& indexType);

public:
    CommandProcessor(const std::string& dataFileName,
                    const std::string& baseName,
                    int order,
                    const std::string& commandFileName,
                    const std::string& outputFileName);

    ~CommandProcessor();

    bool run();
};

#endif