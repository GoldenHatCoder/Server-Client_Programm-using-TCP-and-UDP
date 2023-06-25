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

void sendMessageTCP(int socket) {
    char message[MAX_BUFFER_SIZE];
    printf("Enter the message to send: ");
    fgets(message, MAX_BUFFER_SIZE, stdin);
    message[strcspn(message, "\n")] = '\0';

    send(socket, message, strlen(message), 0);
    printf("Message sent.\n");

    logCommunication(message);
}

void sendMessageUDP(int socket) {
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    char message[MAX_BUFFER_SIZE];
    printf("Enter the message to send: ");
    fgets(message, MAX_BUFFER_SIZE, stdin);
    message[strcspn(message, "\n")] = '\0';

    sendto(socket, message, strlen(message), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    printf("Message sent.\n");

    logCommunication(message);
}

void changeIPAddress() {
    char newIP[16];
    printf("Enter the new IP address: ");
    fgets(newIP, 16, stdin);
    newIP[strcspn(newIP, "\n")] = '\0';

    printf("IP address changed to %s.\n", newIP);
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
    int choice;
    int clientSocket;

    struct sockaddr_in serverAddress;

    // Create TCP socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        printf("Could not create TCP socket.\n");
        return 1;
    }

    // Set server details
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        printf("Connection failed.\n");
        return 1;
    }

    while (1) {
        printf("\n----- MENU -----\n");
        printf("1. Send message (TCP)\n");
        printf("2. Send message (UDP)\n");
        printf("3. Change IP address\n");
        printf("4. Display network traffic\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume the newline character

        switch (choice) {
            case 1:
                sendMessageTCP(clientSocket);
                break;
            case 2:
                sendMessageUDP(clientSocket);
                break;
            case 3:
                changeIPAddress();
                break;
            case 4:
                displayNetworkTraffic();
                break;
            case 5:
                close(clientSocket);
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}
