#include <stdio.h>
#include <string.h>
#include <dirent.h>
#define BUFLEN 2048
#define PORT 8888
#ifndef HTML_H_
#define HTML_H_

void SendHTML(char* directory,SOCKET socket);
void SendHTMLstyle( char* message);
void SendHTMLtext( char* message,char* text);
void SendHTMLhead( char* message,char* title);
void SendHTMLend( char* message);
void SendHTMLbegin( char* message);
char* getPath(char* buf);

#endif /* HTML_H_ */
