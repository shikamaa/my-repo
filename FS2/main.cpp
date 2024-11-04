#include <iostream>
#include <fstream>

#define BUFFER_SIZE 16

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Please provide source and destination files" << std::endl;
        return 1;
    }

    const char* source = argv[1];
    const char* destination = argv[2];

    std::ifstream sourceFile(source, std::ios::in | std::ios::binary);
    if (!sourceFile.is_open()) {
        std::cerr << "Error: could not open source file " << source << std::endl;
        return 1;
    }

    std::ofstream destinationFile(destination, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!destinationFile.is_open()) {
        std::cerr << "Error: could not open destination file " << destination << std::endl;
        return 1;
    }

    char buffer[BUFFER_SIZE];
    long overallBytes = 0;
    while (sourceFile.read(buffer, BUFFER_SIZE) || sourceFile.gcount() > 0) {
        destinationFile.write(buffer, sourceFile.gcount());
        overallBytes += sourceFile.gcount();
    }

    sourceFile.close();
    destinationFile.close();
    std::cout << "Completed copying file. Overall bytes copied: " << overallBytes << std::endl;

    return 0;
}
