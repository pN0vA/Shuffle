#include <iostream>
#include <cstring>

using namespace std;

int main() {
    // shellcode to execute
    char shellcode[] = "PUT SHELLCODE HERE";

    // get size of shellcode
    int size = strlen(shellcode);

    // cast shellcode to a function pointer and execute it
    void (*func)() = (void (*)()) shellcode;
    func();

    return 0;
}
