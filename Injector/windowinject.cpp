#include <iostream>
#include <cstring>
#include <cstdlib>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

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

    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Error initializing Winsock\n";
        return 1;
    }

    // Create socket
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        cerr << "Error creating socket\n";
        WSACleanup(); // clean up Winsock on error
        return 1;
    }

    // Connect to target
    struct sockaddr_in target_addr;
    memset(&target_addr, 0, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    target_addr.sin_addr.s_addr = inet_addr(target_ip);
    target_addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr*)&target_addr, sizeof(target_addr)) == SOCKET_ERROR) {
        cerr << "Error connecting to target\n";
        closesocket(sockfd); // close socket on error
        WSACleanup(); // clean up Winsock on error
        return 1;
    }

    // Get shellcode from user
    cout << "Enter the shellcode to inject: ";
    string shellcode;
    getline(cin, shellcode);

    // Send shellcode to target
    const char* buffer = shellcode.c_str();
    int bytes_written = send(sockfd, buffer, shellcode.length(), 0);
    if (bytes_written == SOCKET_ERROR) {
        cerr << "Error writing to socket\n";
        closesocket(sockfd); // close socket on error
        WSACleanup(); // clean up Winsock on error
        return 1;
    } else if (bytes_written != shellcode.length()) {
        cerr << "Incomplete write to socket\n";
        closesocket(sockfd); // close socket on error
        WSACleanup(); // clean up Winsock on error
        return 1;
    }

    // Clean up and exit
    closesocket(sockfd);
    WSACleanup();
    return 0;
}
