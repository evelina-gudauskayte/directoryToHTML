#include <limits.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <malloc.h>
#include <winsock2.h>
#include "html.h"


void SendHTMLbegin( char* message){
	strcat(message,"<!DOCKTYPE html> <html>");
}

void SendHTMLend(char* message){
	strcat(message,"</html>");
}

void SendHTMLhead(char* message,char* title){
	strcat(message,"<head><h1>");
	strcat(message,title);
	strcat(message,"</h1></head>");
}

void SendHTMLtext(char* message,char* text){
	strcat(message,"<p>");
	strcat(message,text);
	strcat(message,"</p>\n");
}

void SendHTMLstyle( char* message){
	strcat(message, "<style> \n");
	strcat(message, "p{padding: 5px 10px; \n background: #f5f5f5; \n border-left: 2px solid #216E36;}\n");
	strcat(message, "h1 {border: 4px solid green; \n background: #f5f5f5; \n border-radius: 5px; \n text-align: center} \n");
	strcat(message,".special::before {content: \"directory >\"; \n color: red; \n }\n");
	strcat(message, "</style> \n");
}

void SendHTML(char* directory, SOCKET socket){
	char message[BUFLEN]="HTTP/1.1 200 OK\r\nContent-Type: text/html;\r\n\r\n";
	//printf("done 1\n");
	DIR *dir;
	struct dirent *ent;
	int check1dot,check2dot;
		if ((dir = opendir (directory)) != NULL) {
		SendHTMLbegin(message);
		SendHTMLhead(message,directory);
		SendHTMLstyle(message);

		//char* bufToSend = (char*)malloc(BUFLEN*sizeof(char));

		while ((ent = readdir (dir)) != NULL){
			check1dot=strcmp(ent->d_name,".");
			check2dot=strcmp(ent->d_name,"..");

			if(check1dot!=0 && check2dot!=0 ){
				SendHTMLtext(message, ent->d_name);
			}
		}
		SendHTMLend(message);
		closedir (dir);
		if (SOCKET_ERROR == send(socket,message,strlen(message),0)){
			printf("Too many fles in a folder \n");
		}
	} else {
		if (SOCKET_ERROR == send(socket,"HTTP/1.1 200 OK\r\nContent-Type: text/html;\r\n\r\n\nWrong directory or wrong syntax: should be like: \"c:/folder\" OR \"c:\\\\folder\"\n or write \"path=exit\" to exit \n", 155, 0)){
			printf("error\n");
		}
	}
}
char* getPath(char* buf){
	char* path;
	if(strstr(buf,"path=")==NULL || strstr(buf," HTTP")==NULL ){
			return NULL;
	}
	char* begin = strstr(buf, "path=");
	begin= begin +5;
	int counter = 0;
	char* end = strstr(buf, " HTTP");

	int size = end-begin;

	for (int i = 0; i<size-3; i++){
		if (*(begin+i*sizeof(char))=='%' && *(begin+(i+1)*sizeof(char))== '2' && *(begin+(i+2)*sizeof(char))== '0'){
			counter++;
		}
	}
	int newSize = size-counter*2;
	path = (char*)malloc(newSize*sizeof(char));
	int j = 0;
	for (int i =0; i < newSize; i++){
		if (*(begin+j*sizeof(char))=='%' && *(begin+(j+1)*sizeof(char))== '2' && *(begin+(j+2)*sizeof(char))== '0'){
					path[i]=' ';
					j=j+3;
		}else{
			path[i]=*(begin+j*sizeof(char));
			j++;
		}
	}
	path[newSize]='\0';
	return path;
}
