#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>\n";
        return 1;
    }

    const char* path = argv[1];

    int fd1 = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 < 0) {
        perror("Error: file is open uncorrectly");
        return 2;
    }

    int fd2 = dup(fd1);
    if (fd2 < 0) {
        perror("Error: uncorrect dup working");
        close(fd1);
        return 3;
    }

    const char* line1 = "first line\n";
    if (write(fd1, line1, strlen(line1)) < 0) {
        perror("Error: first line is uncorrectly written");
        close(fd1);
        close(fd2);
        return 4;
    }

    const char* line2 = "second line\n";
    if (write(fd2, line2, strlen(line2)) < 0) {
        perror("Error: second line is uncorrectly written");
        close(fd1);
        close(fd2);
        return 5;
    }

    close(fd1);
    close(fd2);

    return 0;
}
