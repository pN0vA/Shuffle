#include <stdio.h>

#define MAX_LINE_LENGTH 100

int main() {
    FILE* file = fopen("misc/misc/chrome.c", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
    return 0;
}
