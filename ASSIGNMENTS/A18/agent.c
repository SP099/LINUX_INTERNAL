/*Doc
Name            : Sushant H Patil
Date            : 13-08-2023
Description     : Implement Terminal protocol using Sockets
Sample input    : take input from user
Sample output   : 
                  ./relay
                  INFO: created relay socket
                  LISTENING: relay server is listening
.                 ............
                  ACCEPTED: relay server accepted connection

                  ./server_plus
                  INFO: created server socket
                  LISTENING: plus server is listening
                  ACCEPTED: accepted a connection
                  Client data  : 10  20  +
                  Result is 30
                  Sending result to client...

                  ./client
                  Enter num1: 10
                  Enter num2: 20
                  Enter arithmetic operator: +
                  INFO: Created relay socket
                  SUCCESS: relay connection successful
                  SERVER IP 127.0.0.1
                  SERVER PORT 6000
                  INFO: Created server socket
                  SUCCESS: Server connection successful
                  RESULT: 30
Doc*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

    if (bind(agentSocket, (struct sockaddr *)&agentAddress, sizeof(agentAddress)) == -1) {
        printf("Binding failed\n");
        return 1;
    }
    if (listen(agentSocket, 5) == -1) {
        printf("Listening failed\n");
        return 1;
    }
    printf("INFO: Agent socket created\n");
    printf("SUCCESS: Agent server is listening\n");

    while (1) {
        // Create client socket for communication with agentSocket
        int clientSocket = accept(agentSocket, NULL, NULL);
        if (clientSocket == -1) {
            printf("INFO: Accepting connection failed\n");
            return 1;
        }
        printf("INFO: ACCEPTED: Agent server connection\n");

        // Main server IP addresses and port numbers
        char mainServerInfo[5][256] = {
            "127.0.0.1 2000",
            "127.0.0.1 2500",
            "127.0.0.1 3000",
            "127.0.0.1 3500",
            "127.0.0.1 4000"
        };

        // Determine the server based on the operation
        char operation[2];
        recv(clientSocket, operation, sizeof(operation), 0);
        int serverIndex = -1;
        switch (operation[0]) {
            case '+':
                serverIndex = 0;
                break;
            case '-':
                serverIndex = 1;
                break;
            case '*':
                serverIndex = 2;
                break;
            case '/':
                serverIndex = 3;
                break;
            case '%':
                serverIndex = 4;
                break;
            default:
                break;
        }
        
        if (serverIndex != -1) {
            send(clientSocket, mainServerInfo[serverIndex], strlen(mainServerInfo[serverIndex]), 0);
        }
        
        // Close the client socket
        close(clientSocket);
    }

    // Close the agent socket
    close(agentSocket);
    return 0;
}
