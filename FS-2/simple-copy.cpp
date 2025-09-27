#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <source-file> <destination-file>\n";
        return 1;
    }

    const char* srcPath = argv[1];
    const char* destPath = argv[2];

    std::ifstream srcFile(srcPath, std::ios::binary);
    if (!srcFile) {
        std::cerr << "Error: Cannot open source file: " << srcPath << "\n";
        return 1;
    }

    std::ofstream destFile(destPath, std::ios::binary);
    if (!destFile) {
        std::cerr << "Error: Cannot open destination file: " << destPath << "\n";
        return 1;
    }

    destFile << srcFile.rdbuf();

    std::cout << "File copied successfully.\n";
    return 0;
}

