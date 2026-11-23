#include "CommandProcessor.h"
#include <sstream>
#include <iostream>

CommandProcessor::CommandProcessor(const std::string& dataFileName,
                                const std::string& baseName,
                                int order,
                                const std::string& commandFileName,
                                const std::string& outputFileName) {
    this->dataFileName = dataFileName;
    this->baseName = baseName;
    this->order = order;
    this->commandFileName = commandFileName;
    this->outputFileName = outputFileName;

    database = new Database(baseName + ".dat");
    idIndex = new BTree(baseName + ".ix1", order, 9);
    nameIndex = new BTree(baseName + ".ix2", order, 15);
}

CommandProcessor::~CommandProcessor() {
    delete database;
    delete idIndex;
    delete nameIndex;
}

void CommandProcessor::writeStatus(std::ofstream& outFile) {
    outFile << "NUMBER OF RECORDS: "
            << database->getRecordCount()
            << ", ID INDEX: "
            << idIndex->getNodeCount()
            << " nodes, NAME INDEX: "
            << nameIndex->getNodeCount()
            << " nodes."
            << std::endl;
}

void CommandProcessor::writeRecord(std::ofstream& outFile, long position) {
    StudentRecord record;

    if (database->readRecord(position, record)) {
        outFile << position
                << ":"
                << record.toPrintableString()
                << std::endl;
    }
}

bool CommandProcessor::buildInitialFiles() {
    std::ifstream dataFile(dataFileName.c_str());

    if (!dataFile) {
        std::cout << "Could not open data file: " << dataFileName << std::endl;
        return false;
    }

    if (!database->createEmpty()) {
        std::cout << "Could not create database file." << std::endl;
        return false;
    }

    if (!idIndex->createEmpty()) {
        std::cout << "Could not create ID index file." << std::endl;
        return false;
    }

    if (!nameIndex->createEmpty()) {
        std::cout << "Could not create name index file." << std::endl;
        return false;
    }

    std::string line;

    while (std::getline(dataFile, line)) {
        StudentRecord record;

        if (StudentRecord::parseLine(line, record)) {
            long position = database->appendRecord(record);

            if (position >= 0) {
                idIndex->insert(record.getId(), position);
                nameIndex->insert(record.getLastName(), position);
            }
        }
    }

    dataFile.close();

    return true;
}

void CommandProcessor::processFindId(std::ofstream& outFile,
                                    const std::string& id) {
    long position = idIndex->searchFirst(id);

    if (position == -1) {
        outFile << "NOT FOUND" << std::endl;
        return;
    }

    writeRecord(outFile, position);
}

void CommandProcessor::processFindName(std::ofstream& outFile,
                                    const std::string& lastName) {
    int resultCount = 0;
    long* results = nameIndex->searchAll(lastName, resultCount);

    if (resultCount == 0) {
        outFile << "NOT FOUND" << std::endl;
        delete[] results;
        return;
    }

    for (int i = 0; i < resultCount; i++) {
        writeRecord(outFile, results[i]);
    }

    delete[] results;
}

void CommandProcessor::processAdd(std::ofstream& outFile,
                                const std::string& id,
                                const std::string& lastName,
                                const std::string& firstName,
                                const std::string& year,
                                const std::string& major,
                                const std::string& email) {
    StudentRecord record(id, lastName, firstName, year, major, email);

    long position = database->appendRecord(record);

    int idSplits = idIndex->insert(id, position);
    int nameSplits = nameIndex->insert(lastName, position);

    outFile << "STUDENT "
            << id
            << " ADDED ("
            << position
            << ";"
            << idSplits
            << ";"
            << nameSplits
            << ")"
            << std::endl;
}

void CommandProcessor::processDump(std::ofstream& outFile,
                            const std::string& indexType) {
    int resultCount = 0;
    long* results = NULL;

    if (indexType == "ID") {
        results = idIndex->dump(resultCount);
    } else if (indexType == "name") {
        results = nameIndex->dump(resultCount);
    } else {
        return;
    }

    for (int i = 0; i < resultCount; i++) {
        writeRecord(outFile, results[i]);
    }

    delete[] results;
}

bool CommandProcessor::run() {
    if (!buildInitialFiles()) {
        std::cout << "Failed while building initial files." << std::endl;
        return false;
    }

    std::ifstream commandFile(commandFileName.c_str());

    if (!commandFile) {
        std::cout << "Could not open command file: " << commandFileName << std::endl;
        return false;
    }

    std::ofstream outFile(outputFileName.c_str());

    if (!outFile) {
        std::cout << "Could not create output file: " << outputFileName << std::endl;
        return false;
    }

    writeStatus(outFile);

    std::string line;

    while (std::getline(commandFile, line)) {
        if (line.length() == 0) {
            continue;
        }

        std::stringstream ss(line);

        std::string command;
        ss >> command;

        outFile << "COMMAND: " << line << std::endl;

        if (command == "find") {
            std::string type;
            std::string value;

            ss >> type >> value;

            if (type == "ID") {
                processFindId(outFile, value);
            } else if (type == "name") {
                processFindName(outFile, value);
            }
        } else if (command == "add") {
            std::string id;
            std::string lastName;
            std::string firstName;
            std::string year;
            std::string major;
            std::string email;

            ss >> id >> lastName >> firstName >> year >> major >> email;

            processAdd(outFile, id, lastName, firstName, year, major, email);
        } else if (command == "dump") {
            std::string by;
            std::string indexType;

            ss >> by >> indexType;

            processDump(outFile, indexType);
        }
    }

    writeStatus(outFile);

    commandFile.close();
    outFile.close();

    return true;
}