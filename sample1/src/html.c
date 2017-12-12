#include <limits.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <malloc.h>
#include <winsock2.h>
#include "html.h"
#define BUFLEN 1024

void SendHTMLbegin( SOCKET socket){
	send(socket,"<!DOCKTYPE html> <html>",23,0);
}

void SendHTMLend(SOCKET socket){
	send(socket,"</html>",7,0);
}

void SendHTMLhead(SOCKET socket,char* title){
	send(socket,"<head><h1>",10,0);
	send(socket,title,strlen(title),0);
	send(socket,"</h1></head>",12,0);
}

void SendHTMLtext(SOCKET socket,char* text){
	send(socket,"<p>",3,0);
	send(socket,text,strlen(text),0);
	send(socket,"</p>\n",5,0);
}

void SendHTMLstyle( SOCKET socket){
	send(socket, "<style> \n", 9,0);
	send(socket, "p{padding: 5px 10px; \n background: #f5f5f5; \n border-left: 2px solid #216E36;}\n", 79, 0 );
	send(socket, "h1 {border: 4px solid green; \n background: #f5f5f5; \n border-radius: 5px; \n text-align: center} \n", 97,0 );
	send(socket,".special::before {content: \"directory >\"; \n color: red; \n }\n",62,0);
	send(socket, "</style> \n",10,0);
}

void SendHTML(char* directory, SOCKET socket){
	DIR *dir;
	struct dirent *ent;
	int check1dot,check2dot;
		if ((dir = opendir (directory)) != NULL) {
		SendHTMLbegin(socket);
		SendHTMLhead(socket,directory);
		SendHTMLstyle(socket);

		while ((ent = readdir (dir)) != NULL){
			check1dot=strcmp(ent->d_name,".");
			check2dot=strcmp(ent->d_name,"..");

			if(check1dot!=0 && check2dot!=0 ){
				SendHTMLtext(socket, ent->d_name);
			}
		}
		SendHTMLend(socket);
		closedir (dir);
	} else {
	  send(socket,"\nWrong directory or wrong syntax: should be like: \"c:/folder\" OR \"c:\\\\folder\"\n or write \"path=exit\" to exit \n", 110, 0);
	}

}
char* getPath(char buf[BUFLEN]){
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
