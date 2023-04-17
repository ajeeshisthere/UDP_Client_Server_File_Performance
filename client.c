#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8765
#define BUF_SIZE 1024
#define FILE_PATH "file_to_send"

int main(int argc, char const *argv[]) {
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in server_address;
    sleep(10);

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set server address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    // Open file to send
    FILE *fp;
    fp = fopen(FILE_PATH, "rb");
    if (fp == NULL) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    // Send file 1000 times
    for (int i = 0; i < 1; i++) {
        printf("Sending file, iteration %d\n", i+1);
        fseek(fp, 0, SEEK_SET);  // reset file pointer
        while (!feof(fp)) {
            int n = fread(buffer, sizeof(char), BUF_SIZE, fp);
            if (n == -1) {
                perror("fread failed");
                exit(EXIT_FAILURE);
            }
            if (sendto(sockfd, buffer, n, 0, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
                perror("sendto failed");
                exit(EXIT_FAILURE);
            }
        }
        if (sendto(sockfd, "END", strlen("END"), 0, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }
        printf("File sent successfully, iteration %d\n", i+1);
    }
        if (sendto(sockfd, "TERMINATE", strlen("TERMINATE"), 0, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }

    fclose(fp);
    close(sockfd);

    return 0;
}
