#include <iostream>
#include <cstdlib>
#include <chrono>
#include <sys/wait.h>
#include <unistd.h>

void do_command(char** argv) {
    auto start_time = std::chrono::high_resolution_clock::now();
    pid_t pid = fork();
    if (pid == 0) {
        execvp(argv[0], argv);
        std::cerr << "error executing command" << std::endl;
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;
        std::cout << "command completed with exit code " << WEXITSTATUS(status)
                  << " and took " << duration.count() << " seconds." << std::endl;
    } else {
        std::cerr << "fork failed" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        
        return 1;
    }
    do_command(argv + 1);
    return 0;
}

