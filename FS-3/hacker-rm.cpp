#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>\n";
        return 1;
    }

    const char* path = argv[1];
    struct stat st;

    if (stat(path, &st) != 0) {
        std::cerr << "Eror: file s not open\n";
        return 2;
    }

    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        std::cerr << "Error: file is not open correctly\n";
        return 3;
    }

    if (lseek(fd, 0, SEEK_SET) == (off_t)-1) {
        std::cerr << "lseek failed: " << strerror(errno) << "\n";
        close(fd);
        return 4;
    }
    
    off_t size = st.st_size;
    char zero = '\0';
    for (off_t i = 0; i < size; ++i) {
        write(fd, &zero, 1);
    }
    close(fd);

    if (unlink(path) != 0) {
        std::cerr << "Error: file is delete uncorrectly \n";
        return 5;
    }

    std::cout << "hacker-rm was processed successfully :)\n";
    return 0;
}
