#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdint.h>
#include <signal.h>

#define SHELLCODE_MAX_SIZE 4096

void handle_sigsegv(int sig) {
    printf("Segmentation fault: Invalid memory access\n");
    exit(1);
}

int main(int argc, char** argv) {

    // Check for string argument
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    // Get the string argument
    char* input = argv[1];
    size_t input_length = strlen(input);

    // Allocate memory for shellcode buffer
    char* shellcode = (char*)malloc(SHELLCODE_MAX_SIZE);
    if (shellcode == NULL) {
        fprintf(stderr, "Failed to allocate memory for shellcode: %s\n", strerror(errno));
        return 1;
    }

    // Convert string to shellcode
    size_t shellcode_size = 0;
    for (int i = 0; i < input_length && shellcode_size < SHELLCODE_MAX_SIZE; i++) {
        shellcode[shellcode_size++] = input[i] ^ 0xff; // XOR with 0xff to avoid null bytes
    }

    // Print shellcode
    printf("Shellcode: ");
    for (int i = 0; i < shellcode_size; i++) {
        printf("\\x%02x", (unsigned char)shellcode[i]);
    }
    printf("\n");

    // Allocate executable memory
    void* exec_mem = mmap(0, shellcode_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (exec_mem == MAP_FAILED) {
        fprintf(stderr, "Failed to allocate executable memory: %s\n", strerror(errno));
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
        fprintf(stderr, "Failed to set up signal handler: %s\n", strerror(errno));
        munmap(exec_mem, shellcode_size);
        free(shellcode);
        return 1;
    }

    // Set the return address
    void (*code)() = (void(*)())exec_mem;
    asm("mov %0, %%rsp; ret" : : "r"(ret_addr));
    code();

    // Free memory
    munmap(exec_mem, shellcode_size);
    free(shellcode);

    return 0;
}

