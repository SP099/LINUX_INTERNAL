#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define AGENT_IP "127.0.0.1"
#define AGENT_PORT 1500

int main() {
    int agentSocket;
    struct sockaddr_in agentAddress;

    // Create agent socket
    agentSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (agentSocket == -1) {
        printf("Error: Agent socket creation failed\n");
        return 1;
    }

    // Populate agent address details
    agentAddress.sin_family = AF_INET;
    agentAddress.sin_port = htons(AGENT_PORT);
    agentAddress.sin_addr.s_addr = inet_addr(AGENT_IP);

    // Establish connection with agent
    if (connect(agentSocket, (struct sockaddr *)&agentAddress, sizeof(agentAddress)) != 0) {
        printf("Agent connection failed\n");
        exit(1);
    }

    printf("INFO: Created agent socket\n");
    printf("SUCCESS: Agent connection successful\n");

    // Read arithmetic operator
    char operatorSymbol[2];
    printf("Enter arithmetic operator [+,-,*,/,%%]: ");
    scanf("%1s", operatorSymbol);

    // Send the operator to agent to receive server information
    send(agentSocket, operatorSymbol, strlen(operatorSymbol), 0);

    char mainServerInfo[256];
    // Receive server information from agent
    recv(agentSocket, mainServerInfo, sizeof(mainServerInfo), 0);

    // Read server IP and port number from mainServerInfo array
    char mainServerIP[16];
    int mainServerPort;
    sscanf(mainServerInfo, "%s %d", mainServerIP, &mainServerPort);

    // Close agent socket
    close(agentSocket);

    int mainServerSocket;
    struct sockaddr_in mainServerAddress;

    // Create server socket
    mainServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mainServerSocket == -1) {
        printf("Server socket creation failed\n");
        return 1;
    }

    // Populate server address details
    mainServerAddress.sin_family = AF_INET;
    mainServerAddress.sin_port = htons(mainServerPort);
    mainServerAddress.sin_addr.s_addr = inet_addr(mainServerIP);

    // Establish connection between client and server
    if (connect(mainServerSocket, (struct sockaddr *)&mainServerAddress, sizeof(mainServerAddress)) == -1) {
        printf("Mainserver connection failed\n");
        return 1;
    }
    
    printf("INFO: Created server socket\n");
    printf("SUCCESS: Server connection successful\n");

    // Read input from user
    int num1, num2;
    printf("Enter num1: ");
    scanf("%d", &num1);
    printf("Enter num2: ");
    scanf("%d", &num2);

    // Store the read input into buffer
    char buffer[256];
    sprintf(buffer, "%d %d %c", num1, num2, operatorSymbol[0]);

    // Send above info to server
    send(mainServerSocket, buffer, strlen(buffer), 0);

    // Receive the result from server
    char result[256];
    recv(mainServerSocket, result, sizeof(result), 0);
    char *cleanResult = strtok(result, "\r\n");
    printf("RESULT: %s\n", cleanResult);

    // Close main server socket
    close(mainServerSocket);

    return 0;
}
