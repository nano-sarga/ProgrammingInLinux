#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdio>

void externalSort(const std::string& input, const std::string& output, size_t R_bytes) {
    std::ifstream in(input);
    if (!in.is_open()) {
        std::cerr << "File is not open\n";
        return;
    }

    std::vector<std::string> lines;         
    std::vector<std::string> blockNames;      
    size_t currentSize = 0;                        
    int blockNum = 0;

    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
        currentSize += line.size() + 1;          

        if (currentSize >= R_bytes) {
            std::sort(lines.begin(), lines.end());
            std::string name = "block_" + std::to_string(blockNum++) + ".txt";
            std::ofstream out(name);
            for (size_t i = 0; i < lines.size(); ++i) {
            out << lines[i] << '\n';
            }

            out.close();

            blockNames.push_back(name);
            lines.clear();
            currentSize = 0;
        }
    }

    if (!lines.empty()) {
        std::sort(lines.begin(), lines.end());
        std::string name = "block_" + std::to_string(blockNum++) + ".txt";
        std::ofstream out(name);
        for (size_t i = 0; i < lines.size(); ++i) {
        out << lines[i] << '\n';
        }

        out.close();

        blockNames.push_back(name);
    }
    
    in.close();

    std::vector<std::ifstream> parts(blockNames.size());   
    std::vector<std::string> currentLine(blockNames.size());   
    std::vector<bool> active(blockNames.size(), true);   

    for (size_t i = 0; i < blockNames.size(); ++i) {
        parts[i].open(blockNames[i]);
        if (!std::getline(parts[i], currentLine[i])) active[i] = false;
    }

    std::ofstream out(output);

    while (true) {
        int minIndex = -1;

        for (size_t i = 0; i < currentLine.size(); ++i) {
            if (!active[i]) continue;
            if (minIndex == -1 || currentLine[i] < currentLine[minIndex])
                minIndex = i;
        }

        if (minIndex == -1) break;   

        out << currentLine[minIndex] << '\n';

        if (!std::getline(parts[minIndex], currentLine[minIndex]))
            active[minIndex] = false;
    }

    out.close();
    
    for (size_t i = 0; i < parts.size(); ++i)
    parts[i].close();

    for (size_t i = 0; i < blockNames.size(); ++i)
    std::remove(blockNames[i].c_str());
}

int main() {
    size_t R = 50 * 1024 * 1024;
    externalSort("input.txt", "sorted.txt", R);
}
