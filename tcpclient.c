// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8001

int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char hello[1024];
	char buffer[1024] = {0};
	char sbuffer[6] = "SEND ";
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "158.196.135.85", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnectionnnnnn Failed \n");
		return -1;
	}
	
	valread = read( sock , buffer, 1024);
	printf("%s\n",buffer );
    while(fgets( hello, 1024, stdin)!=NULL){
        strcpy(buffer, hello);
        write(sock , sbuffer , strlen(sbuffer));
        write(sock , buffer , strlen(buffer));
        printf("message sent\n");
        memset(buffer, 0, sizeof(buffer));
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
    }
	return 0;
}
