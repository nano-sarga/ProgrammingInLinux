#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>\n";
        return 1;
    }

    const char* file_path = argv[1];
    std::ifstream file(file_path, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: cannot open file " << file_path << "\n";
        return 1;
    }

    const size_t buffer_size = 1024;
    std::vector<char> buffer(buffer_size);

    while (file) {
        file.read(buffer.data(), buffer.size());
        std::streamsize bytes_read = file.gcount();
        if (bytes_read > 0) {
            std::cout.write(buffer.data(), bytes_read);
        }
    }

    return 0;
}


