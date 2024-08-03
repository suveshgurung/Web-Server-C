#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 3000

int main() {

    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t address_len = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, address_len) < 0) {
        perror("Sockent binding failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) {
        perror("Listening in socket failed");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &address_len)) < 0) {
        perror("Accepting client failed");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t valRead = read(server_fd, buffer, 1024 - 1);

    printf("%s\n", buffer);
    
    char* returnMessage = "Hello from the sever!!!";
    send(new_socket, returnMessage, strlen(returnMessage), 0);
    printf("Hello message sent to the client\n");

    close(new_socket);
    close(server_fd);

    return 0;

}
