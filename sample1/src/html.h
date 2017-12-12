#include <stdio.h>
#include <string.h>
#include <dirent.h>
#define BUFLEN 1024
#ifndef HTML_H_
#define HTML_H_

void SendHTML(char* directory,SOCKET socket);
void SendHTMLstyle(SOCKET socket);
void SendHTMLtext(SOCKET socket,char* text);
void SendHTMLhead(SOCKET socket,char* title);
void SendHTMLend(SOCKET socket);
void SendHTMLbegin(SOCKET socket);
char* getPath(char buf[BUFLEN]);

#endif /* HTML_H_ */
