#include <fstream>
#include <iostream>
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./read-file <file_path>" << std::endl;
        return 1;
    }

    const char* file_path = argv[1];
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "Error: failed to open file " << file_path << std::endl;
        return 1;
    }

    const size_t buffer_size = 1024;
    char buffer[buffer_size + 1];

    while (!file.eof()) {
        file.read(buffer, buffer_size);
        std::streamsize bytes_read = file.gcount();
        buffer[bytes_read] = '\0';
        std::cout << buffer;
    }

    file.close();
    return 0;
}
