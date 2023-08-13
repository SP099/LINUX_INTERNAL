/*<<Doc
Name            : Sushant H Patil
Date            : 13-08-2023
Description     : Implement Remote command execution using UDP sockets
Sample execution:

                  $ ./udp_server & (Running server in background)
                	[123423]

                  $ ./udp_client
                  Enter any standard LS command :  date
                  Enter no.of times to be executed :  3
                  Wed Apr 28 13:27:19 IST 2020
                  Wed Apr 28 13:27:19 IST 2020
                  Wed Apr (64 bytes of 1th packet received from server, sending ack)
                  2 8 13:27:19 IST 2020 (20 bytes of 2th packet received from server,sending ack)
Doc*/

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

#define SERVER_IP  	"127.0.0.1"
#define SERVER_PORT 	5001
#define SERVER_LENGTH 	10
#define SERVER_BUFF  	20

int main()
{
    int sock_fd,buffer_len,cli_len;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    char serv_buffer[SERVER_BUFF];
    char serv_buffer1[SERVER_BUFF];
    char num_arr[SERVER_BUFF];
    char client[70];
    printf("Server is waiting...\n");
    //create a UDP socket 
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    //bind it to a particular IP address & port) 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serv_addr.sin_port = htons(SERVER_PORT);
    bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    //to get some actual data from client 
    cli_len = sizeof(struct sockaddr_in);
    recvfrom(sock_fd,(void *)serv_buffer,SERVER_BUFF,0,(struct sockaddr *) &cli_addr, &cli_len);
   
    printf("Sender Info:\n");
    printf("Sender IP: %s\n", inet_ntoa(cli_addr.sin_addr));
    printf("Sender Port: %d\n", ntohs(cli_addr.sin_port));
    int k=0,l=0,j=0;

    while(serv_buffer[j] != '\0')
    {
		if(serv_buffer[j] >='0' && serv_buffer[j] <= '9')
		{
			num_arr[k] = serv_buffer[j];
	        k++;
	    } 
		else
		{
			serv_buffer1[l] = serv_buffer[j];
	        l++;
		}
		j++;
    }
    serv_buffer1[l] = '\0';
    num_arr[k] = '\0';
    int num = atoi(num_arr);
	//create a file if its not existed and store o/p of system call to file
    int fd = open("file1.txt",O_CREAT|O_EXCL|O_WRONLY,0774);
    if(fd < 0)
    {
		if(errno == EEXIST)
		{
			fd = open("file1.txt",O_TRUNC|O_WRONLY); // if already file created, truncate it
	    }  
    }
    dup2(fd,1);
    int i;
    for(i = 1; i <=num; i++)
    {
		system(serv_buffer1);
    }
    close(1);
    close(fd);
    int ret,size,recv;
    int f_fd =  open("file1.txt",O_RDONLY);
    while(ret != 0) // send file content to client
    {
		ret = read(f_fd,client,64);
	    size = sendto(sock_fd,client,strlen(client)+1,MSG_CONFIRM,(struct sockaddr *)&cli_addr,sizeof(cli_addr));
        recv = recvfrom(sock_fd,(void *)serv_buffer,SERVER_BUFF,MSG_WAITALL,(struct sockaddr *) &cli_addr, &cli_len);
        if(ret < 64)
			break;
        if(!recv)
		{
			break;
		}
    }

    close(sock_fd);
    close(f_fd);
}
