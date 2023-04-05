#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_FILENAME_LENGTH 100
#define MAX_LINE_LENGTH 100

int main() {
    char filename[MAX_FILENAME_LENGTH];
    std::cout << "\nWhich Template would you like:\n 1. Template 1\n 2. Template 2\n 3. Template 3\n 4. Template 4\n\n :";
    std::cin >> filename;

    FILE* file;
    if (strcmp(filename, "1") == 0) {
        file = fopen("templates/template.cpp", "r");
    } else if (strcmp(filename, "2") == 0) {
        file = fopen("templates/template1.cpp", "r");
    } else if (strcmp(filename, "3") == 0){
        file = fopen("templates/temp.cpp", "r");
    } else if (strcmp(filename, "4") == 0){
        file = fopen("templates/temp3.cpp", "r");
    } else {
        file = fopen(filename, "r");
    }

    if (file == NULL) {
        std::cout << "Failed to open file.\n";
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        std::cout << line;
    }

    fclose(file);
    return 0;
}
