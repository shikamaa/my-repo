#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

void copyFile(const char* sourcePath, const char* destPath) {
    int srcFD = open(sourcePath, O_RDONLY);
    if (srcFD < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    struct stat srcStat;
    if (fstat(srcFD, &srcStat) < 0) {
        perror("Error getting file stats");
        close(srcFD);
        exit(EXIT_FAILURE);
    }

    int destFD = open(destPath, O_WRONLY | O_CREAT | O_TRUNC, srcStat.st_mode);
    if (destFD < 0) {
        perror("Error opening destination file");
        close(srcFD);
        exit(EXIT_FAILURE);
    }

    const size_t bufferSize = 4096;
    std::vector<char> buffer(bufferSize, 0);
    size_t totalBytes = 0, dataBytes = 0, holeBytes = 0;

    while (true) {
        ssize_t bytesRead = read(srcFD, buffer.data(), bufferSize);
        if (bytesRead < 0) {
            perror("Error reading source file");
            close(srcFD);
            close(destFD);
            exit(EXIT_FAILURE);
        }
        if (bytesRead == 0)
            break;

        for (ssize_t i = 0; i < bytesRead; ++i) {
            if (buffer[i] == 0) {
                holeBytes++;
            } else {
                dataBytes++;
            }
        }

        if (write(destFD, buffer.data(), bytesRead) != bytesRead) {
            perror("Error writing to destination file");
            close(srcFD);
            close(destFD);
            exit(EXIT_FAILURE);
        }

        totalBytes += bytesRead;
    }

    close(srcFD);
    close(destFD);

    std::cout << "Successfully copied " << totalBytes << " bytes (data: " 
              << dataBytes << ", hole: " << holeBytes << ")." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <source-file> <destination-file>" << std::endl;
        return EXIT_FAILURE;
    }

    const char* sourcePath = argv[1];
    const char* destPath = argv[2];

    copyFile(sourcePath, destPath);
    return EXIT_SUCCESS;
}
