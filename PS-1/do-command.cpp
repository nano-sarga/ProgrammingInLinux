#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>

void do_command(char** argv) {
    auto start = std::chrono::steady_clock::now();

    pid_t pid = fork();
    
    if (pid < 0) {
        std::perror("fork");
        return;
    }
    
    if (pid == 0) {
        execvp(argv[0], argv);
        std::perror("execvp");
        _exit(1);
    }

    int status;
    waitpid(pid, &status, 0);

    auto end = std::chrono::steady_clock::now();
    double time = std::chrono::duration<double>(end - start).count();

    std::cout << "Command completed with " << WEXITSTATUS(status)
              << " exit code and took " << time << " seconds.\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command> [args...]\n";
        return 1;
    }

    do_command(&argv[1]);
    return 0;
}
