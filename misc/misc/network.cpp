#include <iostream>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <ifaddrs.h>

int main() {
    std::vector<std::string> ips;

    struct ifaddrs* ifa;
    getifaddrs(&ifa);

    for (struct ifaddrs* i = ifa; i != nullptr; i = i->ifa_next) {
        if (i->ifa_addr == nullptr) {
            continue;
        }

        if (i->ifa_addr->sa_family == AF_INET) {
            
            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &((struct sockaddr_in*)i->ifa_addr)->sin_addr, ip, INET_ADDRSTRLEN);

            ips.push_back(ip);
        }
    }

    freeifaddrs(ifa);

    std::cout << "IP addresses on your network:" << std::endl;
    for (const auto& ip : ips) {
        std::cout << "- " << ip << std::endl;
    }

    return 0;
}
