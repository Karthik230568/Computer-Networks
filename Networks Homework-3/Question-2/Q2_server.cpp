#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLen = sizeof(clientAddr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error: Socket creation failed\n";
        return 1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error: bind failed\n";
        close(sockfd);
        return 1;
    }

    std::cout << "UDP Server listening on port " << PORT << "...\n";
    int msgCount = 0;

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                         (struct sockaddr*)&clientAddr, &clientLen);
        if (n < 0) {
            std::cerr << "Error: recvfrom failed\n";
            continue;
        }

        msgCount++;
        std::cout << "[Msg #" << msgCount << "] Client says: " << buffer << "\n";

        // Check for quit signal
        if (std::string(buffer) == "quit") {
            std::cout << "Client disconnected. Shutting down.\n";
            break;
        }

        std::string reply = "[ACK #" + std::to_string(msgCount) + "] " + std::string(buffer);
        if (sendto(sockfd, reply.c_str(), reply.size(), 0,
                   (struct sockaddr*)&clientAddr, clientLen) < 0) {
            std::cerr << "Error: sendto failed\n";
        }
    }

    close(sockfd);
    return 0;
}