#include <iostream>
#include <fstream>
#include <string>

#define MAX_LINE_LENGTH 100

int main() {
    std::ifstream file("misc/misc/chrome.c");
    if (!file.is_open()) {
        std::cout << "Failed to open file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
    return 0;
}
