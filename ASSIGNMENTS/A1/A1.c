/*
Name              : Sushant Patil
Date              : 13/07/2023
Description       : Implement a cp(copy) command with –p option
Sample execution  : When no arguments are passed ./my_copy Insufficient arguments
                    Usage:- ./my_copy [option]  
                    When destination file is not exists ./my_copy source.txt dest.txt . New dest.txt file is created and source.txt file will be copied to dest.txt file
                    When destination file exists ./my_copy source.txt dest.txt File “dest.txt” is already exists. Do you want to overwrite (Y/n)
                    When –p option passed ./my_copy –p source.txt dest.txt Permissions also copied from source file to destination file
*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>

//function to copy data from src to destination
void my_cp(int s_fd, int d_fd)
{
    char buff[1024];
    int ret;

    do
    {
	// read data from src file
	ret = read(s_fd, buff, 1024);
	// write data to destination file
	write(d_fd, buff, ret);

    }while(ret != 0);
}

int main(int argc, char *argv[])
{
    int src, dest, s_fd, d_fd;
    int flag = 0; // flag to check status, -p is passed or not
    struct stat statbuf;
    char ch;


    // validation of command line arguments
    if(argc == 1)
    {
	printf("Error: Insufficient arguments\nUsage: ./my_copy [option] <source file> <destination file>\n");
	exit(1);
    }
    else if(argc == 2)
    {
	printf("Error : missing file operands\n");
	exit(1);
    }
    else if((strcmp(argv[2], "-p") == 0) && argc == 3)
    {
	printf("Error : missing destination file operands\n");
	exit(1);
    }
    

    // as per the -p option passed, set the variable values
    if(strcmp(argv[1], "-p") == 0)
    {
	flag = 1; // if -p passed make it 1
	src = 2;
	dest = 3;
    }
    else
    {
	src = 1;
	dest = 2;
    }

    // open source file
    s_fd = open(argv[src], O_RDONLY);
    // if file not open, print error and terminate prgm
    if(s_fd == -1)
    {
	perror("Open");
	exit(1);
    }

    // read src file details
    fstat(s_fd, &statbuf);

    if(flag)
    {
	// if '-p' passed, then copy file permission to dest file
	d_fd = open(argv[dest], O_WRONLY | O_CREAT | O_EXCL, statbuf.st_mode);
    }
    else
    {
	// if '-p' not passed, no need to copy permissions
	d_fd = open(argv[dest], O_WRONLY | O_CREAT | O_EXCL);
    }

    // if destination file already exist
    if(d_fd == -1)
    {
	if(errno == EEXIST)
	{
	    // ask user to overwrite content
	   printf("file '%s' already exists. Do you want to overwrite it? (y/n): ",argv[dest]);
	    scanf(" %c", &ch);
	    // if user press yes, then overwrite content
	    if(ch == 'y' || ch == 'Y')
	    {
		d_fd = open(argv[dest], O_WRONLY | O_TRUNC);
		// if user entered -p , copy src file permission to dest file
		if(flag)
		{
		    fchmod(d_fd, statbuf.st_mode);
		}
		// call copy function
		my_cp(s_fd, d_fd);
                printf("data copied\n");
                exit(1);
	    }
	    else
	    {

		close(s_fd);
		exit(1);
	    }
	}
    }

    // call copy function
    my_cp(s_fd, d_fd);
    printf("New %s(destination file) is created and %s(source file) will be copied to %s(destination file)\n",argv[dest],argv[src],argv[dest]);
    return 0;
}
