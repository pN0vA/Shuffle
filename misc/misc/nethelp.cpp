#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " IP_ADDRESS" << endl;
        return 1;
    }

    string ip_address(argv[1]);

    stringstream command;
    command << "nmap -p- -T4 " << ip_address;

    FILE* pipe = popen(command.str().c_str(), "r");
    if (!pipe) {
        cerr << "Failed to execute Nmap command" << endl;
        return 1;
    }

    char buffer[128];
    vector<string> lines;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        lines.push_back(buffer);
    }

    pclose(pipe);

    vector<int> open_ports;
    for (auto& line : lines) {
        size_t pos = line.find("/tcp");
        if (pos != string::npos) {
            string port_str = line.substr(0, pos);
            int port = atoi(port_str.c_str());
            open_ports.push_back(port);
        }
    }

    cout << "Open ports on " << ip_address << ":" << endl;
    for (int port : open_ports) {
        cout << "- " << port << endl;
    }

    return 0;
}
