#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "html.h"
#define PORT 8888
#define BUFLEN 1024


int main(int argc , char *argv[]){

	char recvbuf[BUFLEN];
    WSADATA wsa;
    SOCKET s , newSocket;
    struct sockaddr_in server , client;
    int c,nam,flag;
    char *message;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    puts("Initialised.\n");

    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET){
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    puts("Socket created.\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT );

    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR){
        printf("Bind failed with error code : %d" , WSAGetLastError());
    }

    puts("Bind done");

    listen(s , 3); //слушаем только 1 клиента

    puts("Waiting for incoming connections...");

   // flag=1;
	c = sizeof(struct sockaddr_in);

	while(flag!=0){
		newSocket = accept(s , (struct sockaddr *)&client, &c);
		if (newSocket == INVALID_SOCKET){
			printf("accept failed with error code : %d" , WSAGetLastError());
		}
		puts("Connection accepted");
		message = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

    	nam = recv(newSocket, recvbuf, BUFLEN, 0);
    	printf("%d\n",nam);
    	char* path = getPath(recvbuf);
    	if (path == NULL){
    		send(newSocket,message,strlen(message),0);
    		send(newSocket,"Write \"/?path=directory\"",24,0);
    	}else{
			if((flag = strcmp(path, "exit"))==0){
				break;
			}
			/*printf("PATH:%s\n",path);
			printf(recvbuf);*/
			send(newSocket,message,strlen(message),0);
			SendHTML(path,newSocket);
			free(path);
    		}
    	printf("%d\n",flag);
    }

    puts("EXIT");
    closesocket(newSocket);
    closesocket(s);
    WSACleanup();
    return 0;
}
