#include <iostream>
#include <fstream>
#include <cstdlib>
#include "CommandProcessor.h"

bool fileExists(const std::string& fileName) {
    std::ifstream file(fileName.c_str());
    return file.good();
}

int main(int argc, char* argv[]) {
    if (argc < 6) {
        std::cout << "ERROR: Insufficient arguments." << std::endl;
        std::cout << "Usage: btree <datafile> <name> <order> <commandfile> <outputfile>" << std::endl;
        return 1;
    }

    std::string dataFileName = argv[1];
    std::string baseName = argv[2];
    int order = std::atoi(argv[3]);
    std::string commandFileName = argv[4];
    std::string outputFileName = argv[5];

    if (order < 3) {
        std::cout << "ERROR: B-tree order must be at least 3." << std::endl;
        return 1;
    }

    if (!fileExists(dataFileName)) {
        std::cout << "ERROR: Data file does not exist: "
                << dataFileName
                << std::endl;
        return 1;
    }

    if (!fileExists(commandFileName)) {
        std::cout << "ERROR: Command file does not exist: "
                << commandFileName
                << std::endl;
        return 1;
    }

    CommandProcessor processor(
        dataFileName,
        baseName,
        order,
        commandFileName,
        outputFileName
    );

    if (!processor.run()) {
        std::cout << "ERROR: Program failed while processing files." << std::endl;
        return 1;
    }

    return 0;
}