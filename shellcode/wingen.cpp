#include <iostream>
#include <cstring>
#include <Windows.h>

#define SHELLCODE_MAX_SIZE 4096

int main(int argc, char** argv) {

    // Check for string argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <string>\n";
        return 1;
    }

    // Get the string argument
    char* input = argv[1];
    size_t input_length = strlen(input);

    // Allocate memory for shellcode buffer
    char* shellcode = (char*)malloc(SHELLCODE_MAX_SIZE);
    if (shellcode == NULL) {
        std::cerr << "Failed to allocate memory for shellcode: " << GetLastError() << "\n";
        return 1;
    }

    // Convert string to shellcode
    size_t shellcode_size = 0;
    for (int i = 0; i < input_length && shellcode_size < SHELLCODE_MAX_SIZE; i++) {
        shellcode[shellcode_size++] = input[i] ^ 0xff; // XOR with 0xff to avoid null bytes
    }

    // Print shellcode
    std::cout << "Shellcode: ";
    for (int i = 0; i < shellcode_size; i++) {
        printf("\\x%02x", (unsigned char)shellcode[i]);
    }
    std::cout << "\n";

    // Allocate executable memory
    LPVOID exec_mem = VirtualAlloc(NULL, shellcode_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (exec_mem == NULL) {
        std::cerr << "Failed to allocate executable memory: " << GetLastError() << "\n";
        free(shellcode);
        return 1;
    }

    // Copy shellcode to executable memory
    memcpy(exec_mem, shellcode, shellcode_size);

    // Calculate the return address
    void* ret_addr = (void*)((uintptr_t)exec_mem + shellcode_size);

    // Set the return address
    void (*code)() = (void(*)())exec_mem;
    __asm {
        mov rsp, ret_addr
        jmp code
    }

    // Free memory
    VirtualFree(exec_mem, 0, MEM_RELEASE);
    free(shellcode);

    return 0;
}
