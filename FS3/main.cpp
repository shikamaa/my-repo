#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: " << argv[0] << " <файл для удаления>" << std::endl;
        return 1;
    }

    const char* filePath = argv[1];
    struct stat fileInfo;

    if (stat(filePath, &fileInfo) != 0) {
        std::cerr << "Ошибка: файл не существует." << std::endl;
        return 1;
    }

    int fd = open(filePath, O_WRONLY);
    if (fd == -1) {
        std::cerr << "Ошибка: не удалось открыть файл." << std::endl;
        return 1;
    }

    off_t size = fileInfo.st_size;
    char* buffer = new char[size];
    memset(buffer, '\0', size);
    write(fd, buffer, size);
    
    delete[] buffer;
    close(fd);
    unlink(filePath);

    return 0;
}
