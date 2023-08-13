#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define  SERVER1_PORT   3000
#define  SERVER1_IP     "127.0.0.1"

int main()
{
    //variable declaration
    int server_fd;
    struct sockaddr_in servaddr;
    
    //create server socket
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd == -1)
    {
		printf("server socket creation failed");
	    return 1;
    }

    //bind it to a particular IP address and port
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER1_PORT);
    servaddr.sin_addr.s_addr = inet_addr(SERVER1_IP);
    if(bind(server_fd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
    {
		printf("Binding failed");
	    return 1;
    }
    if(listen(server_fd,5) == -1)
    {
		printf("Listening failed");
	    return 1;
    }
    printf("INFO:created server1 socket\n");
    printf("LISTENING:plus server is listening\n");

    while(1)
    {
		//accept connection from client
	    int cli_fd = accept(server_fd,NULL,NULL);
	    if(cli_fd == -1)
	    {
			printf("Accept failed");
	        return 1;
	    }
	    printf("ACCEPTED:accepted a connection\n");

	    //receiving data from client
	    char buffer[256];
	    recv(cli_fd,buffer,sizeof(buffer),0);

	    //reading infomation from buffer
	    int num1,num2;
	    char operator;
	    sscanf(buffer,"%d %d %c",&num1,&num2,&operator);

	    //perform the plus operation
	    int result = num1*num2;
	    char resultstr[256];
	    sprintf(resultstr, "Result is %d\n", result);
	    printf("Client data: %d %d %c\n", num1, num2, operator);
	    printf("%s", resultstr);

	    //send the result client
	    send(cli_fd,resultstr,strlen(resultstr),0);

	    //close client socket
	    close(cli_fd);
    }
    //close server socket
    close(server_fd);
    return 0;
}
