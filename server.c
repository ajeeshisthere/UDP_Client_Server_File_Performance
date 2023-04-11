#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8765
#define BUF_SIZE 1024

int main(int argc, char const *argv[]) {
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in server_address, client_address;
    int client_address_len = sizeof(client_address);

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Receive file from client
        FILE *fp;
        fp = fopen("received_file", "wb");
        while (1) {
            memset(&buffer, 0, sizeof(buffer));
            int n = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&client_address, &client_address_len);
            if (n == -1) {
                perror("recvfrom failed");
                exit(EXIT_FAILURE);
            } else if (strcmp(buffer, "END") == 0) {
                break;
            } else if (strcmp(buffer, "TERMINATE") == 0) {
                return 0;
            } else {
                fwrite(buffer, sizeof(char), n, fp);
            }
        }
        fclose(fp);
        printf("File received successfully\n");
    }

    return 0;
}

