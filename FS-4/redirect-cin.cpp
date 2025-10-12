#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string>

void initialize(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>\n";
        return;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Error: file is open uncorretly");
        return;
    }

    if (dup2(fd, STDIN_FILENO) < 0) {
        perror("Error: redirect was working uncorrectly");
        close(fd);
        return;
    }

    close(fd);
}

int main(int argc, char** argv) {
    initialize(argc, argv);

    std::string input;
    std::cin >> input;

    std::string reversed(input.rbegin(), input.rend());
    std::cout << reversed << std::endl;

    return 0;
}
