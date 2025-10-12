#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <source> <destination>\n";
        return 1;
    }

    int src = open(argv[1], O_RDONLY);
    if (src < 0) {
        perror("Error: source is open uncorrectly");
        return 2;
    }

    int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        perror("Error: destination is open uncorrectly");
        close(src);
        return 3;
    }

    char buffer[4096];
    ssize_t bytes_read;
    size_t total = 0, data_bytes = 0, hole_bytes = 0;

    while ((bytes_read = read(src, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytes_read; ++i) {
            if (buffer[i] == '\0') hole_bytes++;
            else data_bytes++;
        }

        if (write(dest, buffer, bytes_read) != bytes_read) {
            perror("write");
            close(src);
            close(dest);
            return 1;
        }

        total += bytes_read;
    }

    if (bytes_read < 0) {
        perror("read");
    }

    close(src);
    close(dest);

    std::cout << "Successfully copied " << total 
              << " bytes (data: " << data_bytes 
              << ", hole: " << hole_bytes << ").\n";

    return 0;
}