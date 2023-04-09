#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <signal.h>
#include <array>

#define SHELLCODE_MAX_SIZE 4096

void handle_sigsegv(int) {
    std::cerr << "Segmentation fault: Invalid memory access\n";
    exit(1);
}

int main(int argc, char** argv) {

    // Check for string argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <string>\n";
        return 1;
    }

    // Get the string argument
    const char* input = argv[1];
    size_t input_length = strlen(input);

    // Allocate memory for shellcode buffer
    std::array<char, SHELLCODE_MAX_SIZE> shellcode;
    size_t shellcode_size = 0;

    // Convert string to shellcode
    for (size_t i = 0; i < input_length && shellcode_size < SHELLCODE_MAX_SIZE; i++) {
        shellcode[shellcode_size++] = input[i] ^ 0xff; // XOR with 0xff to avoid null bytes
    }

    // Print shellcode
    std::cout << "Shellcode: ";
    for (size_t i = 0; i < shellcode_size; i++) {
        printf("\\x%02x", (unsigned char)shellcode[i]);
    }
    std::cout << "\n";

    // Allocate executable memory
    void* exec_mem = mmap(NULL, shellcode_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (exec_mem == MAP_FAILED) {
        std::cerr << "Failed to allocate executable memory: " << strerror(errno) << "\n";
        return 1;
    }

    // Copy shellcode to executable memory
    memcpy(exec_mem, shellcode.data(), shellcode_size);

    // Calculate the return address
    void* ret_addr = (void*)((uintptr_t)exec_mem + shellcode_size);

    // Set up SIGSEGV handler to catch invalid memory access
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigsegv;
    if (sigaction(SIGSEGV, &sa, NULL) == -1) {
        std::cerr << "Failed to set up signal handler: " << strerror(errno) << "\n";
        munmap(exec_mem, shellcode_size);
        return 1;
    }

    // Set the return address
    void (*code)() = (void(*)())exec_mem;
    asm volatile ("mov lr, %0; bx lr" : : "r"(ret_addr));
    code();

    // Free memory
    munmap(exec_mem, shellcode_size);

    return 0;
}
