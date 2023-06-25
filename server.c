#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pcap.h>

#define MAX_BUFFER_SIZE 1024
#define LOG_FILE "communication.log"

void logCommunication(const char *message) {
    FILE *file = fopen(LOG_FILE, "a");
    if (file == NULL) {
        printf("Failed to open log file.\n");
        return;
    }

    fprintf(file, "%s\n", message);
    fclose(file);
}

void handleTCPClient(int socket) {
    char message[MAX_BUFFER_SIZE];
    ssize_t bytesRead = recv(socket, message, MAX_BUFFER_SIZE - 1, 0);
    if (bytesRead > 0) {
        message[bytesRead] = '\0';
        printf("Received message: %s\n", message);
        logCommunication(message);
    } else {
        printf("Failed to receive message.\n");
    }
}

void handleUDPClient(int socket) {
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);

    char message[MAX_BUFFER_SIZE];
    ssize_t bytesRead = recvfrom(socket, message, MAX_BUFFER_SIZE - 1, 0, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (bytesRead > 0) {
        message[bytesRead] = '\0';
        printf("Received message: %s\n", message);
        logCommunication(message);
    } else {
        printf("Failed to receive message.\n");
    }
}

void displayNetworkTraffic() {
    char errorBuffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errorBuffer);
    if (handle == NULL) {
        printf("Failed to open network interface: %s\n", errorBuffer);
        return;
    }

    struct pcap_pkthdr header;
    const u_char *packet;

    while (1) {
        packet = pcap_next(handle, &header);
        printf("Captured a packet with length of [%d]\n", header.len);
    }

    pcap_close(handle);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;

    // Create TCP socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        printf("Could not create TCP socket.\n");
        return 1;
    }

    // Set server details
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        printf("Binding failed.\n");
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 3) < 0) {
        printf("Listening failed.\n");
        return 1;
    }

    printf("Server is listening on port 12345...\n");

    while (1) {
        socklen_t clientAddressLength = sizeof(clientAddress);
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            printf("Acceptance failed.\n");
            return 1;
        }

        int choice;
        printf("\n----- MENU -----\n");
        printf("1. Handle TCP message\n");
        printf("2. Handle UDP message\n");
        printf("3. Display network traffic\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume the newline character

        switch (choice) {
            case 1:
                handleTCPClient(clientSocket);
                break;
            case 2:
                handleUDPClient(clientSocket);
                break;
            case 3:
                displayNetworkTraffic();
                break;
            case 4:
                close(clientSocket);
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice.\n");
                break;
        }

        close(clientSocket);
    }
}
