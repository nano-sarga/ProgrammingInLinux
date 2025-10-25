#include <iostream>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>\n";
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        std::cerr << "Error: cannot open file\n";
        return 1;
    }

    char buf[4096];
    ssize_t n;
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        ssize_t written = 0;
        while (written < n) {
            ssize_t w = write(STDOUT_FILENO, buf + written, n - written);
            if (w < 0) {
		    std::cerr << "Write error\n";
                close(fd);
                return 1;
            }
            written += w;
        }
    }

    if (n < 0) {
	    std::cerr << "Read error\n";
        close(fd);
        return 1;
    }

    if (close(fd) < 0) {
        perror("close");
        return 1;
    }

}

