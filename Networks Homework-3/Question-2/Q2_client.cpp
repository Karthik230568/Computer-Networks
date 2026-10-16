#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error: socket creation failed\n";
        return 1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    std::cout << "UDP Client ready. Type 'quit' to exit.\n";

    std::string msg;
    while (true) {
        std::cout << "Enter message: ";
        if (!std::getline(std::cin, msg) || msg.empty()) continue;

        // Send message to server
        if (sendto(sockfd, msg.c_str(), msg.size(), 0,
                   (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            std::cerr << "Error: sendto failed\n";
            continue;
        }

        if (msg == "quit") break;

        // Receive reply from server
        memset(buffer, 0, BUFFER_SIZE);
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, NULL, NULL);
        if (n < 0) {
            std::cerr << "Error: recvfrom failed\n";
            continue;
        }

        std::cout << "Server replied: " << buffer << "\n";
    }

    close(sockfd);
    return 0;
}