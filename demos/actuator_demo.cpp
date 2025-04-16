#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctime>
#include <thread>

#define PORT 9002
#define BUFFER_SIZE 4096

int main()
{
    char buffer[BUFFER_SIZE];
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
    if (inet_pton(AF_INET, "127.0.0.1", &sock_addr.sin_addr) <= 0)
    {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    if (connect(fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Connected to server at " << "127.0.0.1" << ":" << PORT << std::endl;

    while (true)
    {
        int bytes_received = recv(fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0)
        {
            break;
        }
        else
        {
            std::cout << "Message from client: " << buffer << std::endl;
        }
    }

    close(fd);
}
