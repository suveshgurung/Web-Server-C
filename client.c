#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 3000

int main() {

    int client_fd, status;
    struct sockaddr_in server_addr;
    socklen_t address_len = sizeof(server_addr);

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if ((status = connect(client_fd, (struct sockaddr *)&server_addr, address_len)) < 0) {
        perror("Connection failed\n");
        exit(EXIT_FAILURE);
    }

    char* message = "A"; 
    send(client_fd, message, strlen(message), 0);
    printf("Hello message sent\n");

    char buffer[1024];
    int valRead = read(client_fd, buffer, 1024 - 1);

    printf("%s\n", buffer);

    close(client_fd);

    return 0;
}
