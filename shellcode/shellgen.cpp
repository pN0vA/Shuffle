#include <iostream>
#include <execinfo.h>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <errno.h>
#include <sys/mman.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>

#define SHELLCODE_MAX_SIZE 4096

void handle_sigsegv(int sig) {
    std::cerr << "Segmentation fault: Invalid memory access at address " << reinterpret_cast<void*>(static_cast<uintptr_t>(sig)) << "\n";

    // get the backtrace and print it to STDERR
    const int max_backtrace_frames = 10;
    void* array[max_backtrace_frames];
    size_t size = backtrace(array, max_backtrace_frames);
    backtrace_symbols_fd(array, size, STDERR_FILENO);

    exit(1);
}

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
        std::cerr << "Failed to allocate memory for shellcode: " << strerror(errno) << "\n";
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
    void* exec_mem = mmap(0, shellcode_size + 4096, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS | MAP_EXECUTABLE, -1, 0);
    if (exec_mem == MAP_FAILED) {
        std::cerr << "Failed to allocate executable memory: " << strerror(errno) << "\n";
        free(shellcode);
        return 1;
    }

    // Copy shellcode to executable memory
    memcpy(exec_mem, shellcode, shellcode_size);

    // Calculate the return address
    void* ret_addr = (void*)((uintptr_t)exec_mem + shellcode_size);

    // Set up SIGSEGV handler to catch invalid memory access
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigsegv;
    if (sigaction(SIGSEGV, &sa, NULL) == -1) {
        std::cerr << "Failed to set up signal handler: " << strerror(errno) << "\n";
        munmap(exec_mem, shellcode_size + 4096);
        free(shellcode);
        return 1;
    }


    // Set the return address
    void (*code)() = (void(*)())exec_mem;
    asm("mov %0, %%rsp; jmp *%1" : : "r"((char*)ret_addr - 8), "r"(ret_addr));

    // Execute the shellcode
    code();

    // Free memory
    munmap(exec_mem, shellcode_size + 4096);
    free(shellcode);
    return 0;
}
