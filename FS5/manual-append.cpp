#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filepath>" << std::endl;
        return 1;
    }

    const char* filePath = argv[1];
    int fd1 = open(filePath, O_WRONLY | O_CREAT, 0644);
    if (fd1 == -1) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    
    int fd2 = dup(fd1);
    if (fd2 == -1) {
        std::cerr << "Error: Unable to duplicate file descriptor." << std::endl;
        close(fd1);
        return 1;
    }

    if (write(fd1, "first line\n", 11) == -1) {
        std::cerr << "Error: Unable to write to file." << std::endl;
        close(fd1);
        close(fd2);
        return 1;
    }

    if (write(fd2, "second line\n", 12) == -1) {
        std::cerr << "Error: Unable to write to file." << std::endl;
        close(fd1);
        close(fd2);
        return 1;
    }

    close(fd1);
    close(fd2);

    return 0;
}
