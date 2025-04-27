#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctime>
#include <thread>
#include "../include/secrets.h"

#define PORT 9001
#define BUFFER_SIZE 4096

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("Failed to set REUSEADDR");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sockaddr;
    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, LOCAL_HOST, &sock_addr.sin_addr) <= 0)
    {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    if (connect(fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Connected to server at " << LOCAL_HOST << ":" << PORT << std::endl;

    while (true)
    {
        int random_number = rand() % 100;
        std::string message = "{\"temperature\": " + std::to_string(random_number) + ", \"humidity\": " + std::to_string(random_number) + "}";
        std::cout << "Message: " << message << std::endl;
        const char *c_str_message = message.c_str();
        int sent_bytes = send(fd, c_str_message, strlen(c_str_message), 0);
        if (sent_bytes <= 0)
        {
            std::cout << "Disconnected from client";
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    close(fd);
}
