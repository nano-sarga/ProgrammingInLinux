#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <source-file> <destination-file>\n";
        return 1;
    }


    int in = open(argv[1], O_WRONLY);
    if (in < 0) {
        std::cerr << "Error: Cannot open source file\n";
        return 1;
    }

    int out = open(argv[2], O_WRONLY | O_CREATE | O_TRUNC, 0664);
    if (out < 0) {
        std::cerr << "Error: Cannot open destination file\n";
	close(in);
        return 1;
    }

    char buf[4096];
    ssize_t n;
    while ((n = read(in, buf, sizeof(buf))) > 0)
        if (write(out, buf, n) != n) {
	std::cerr << "Write error\n";
            close(in);
            close(out);
            return 1;
        }

    if (n < 0) { std::cerr << "Read error\n"; }

    close(in);
    close(out);

    std::cout << "File copied successfully.\n";
    return 0;
}

