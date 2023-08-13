#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define SERVER_IP_ADDRESS 	"127.0.0.1"
#define SERVER_PORT       	5001
#define CLIENT_BUFF_SIZE	20
#define SIZE                64

int main()
{
    int sock_fd,c_size,c_size1;
    char client_buff[CLIENT_BUFF_SIZE];
    char client_buff1[CLIENT_BUFF_SIZE];
    char c[CLIENT_BUFF_SIZE];
    char c1[SIZE];
    c1[SIZE] = '\0';
    struct sockaddr_in serv_addr;
    //create a client socket 
    if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("Error: Could not create socket\n");
    	return 1;
    }
    
    //server's address details 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);
    //get the message from client 
    printf("Enter any standard LS command:");
    scanf("%[^\n]s",client_buff);
    printf("Enter no.of times to be executed:");
    scanf("%s",client_buff1);
	strcpy(c,client_buff);
    strcat(c,client_buff1);
    printf("%s",c);
    //send the message to server 
    c_size = sendto(sock_fd, c, strlen(c) + 1, 0,(struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(c_size)
		printf("Message sent to server successsfully, please check\n");
    else
		printf("Error: Message sending failed\n");
    int r;
    int count = 0;
    char ack[10] = {"Recived"};
    memset(c1,64,'\0');
    while(1) 
    {
		r = recvfrom(sock_fd,(void*)c1,SIZE,MSG_WAITALL,(struct sockaddr *)NULL,NULL);
        printf("%s",c1);
        count++;
        if(strlen(c1) < 64)
		{
			r = strlen(c1);
			printf("(%d bytes of %d packet received from server,sending ack)",r,count);
            break;
        }
        printf("(%d bytes of %d packet received from server,sending ack)",r,count);
        c_size = sendto(sock_fd, ack, strlen(c) + 1, MSG_CONFIRM,(struct sockaddr *)&serv_addr, sizeof(serv_addr));
    }
    close(sock_fd);
}
