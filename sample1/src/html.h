/*
 * html.h
 *
 *  Created on: 14.11.2017
 *      Author: evelina
 */
#include <stdlib.h>
#include <string.h>
#ifndef HTML_H_
#define HTML_H_

void htmlHEAD(FILE* list, char* Title){
	fopen(list, "a");
	fprintf(list, "\n \v <head> \n \v \v <h1>");
	for (int i = 0; *Title[i]!="\0";i++){
		fprintf(list, "%c" , Title[i]);
	}
	fprintf(list, " \n \v \v </h1> \n \v </head> \n ");
	fclose(list);
}
void htmlBEGIN(FILE* list){
	fopen(list, "w");
	fprintf(list, "<html>");
	fclose(list);
}
void htmlEND(FILE* list){
	fopen(list, "a");
	fprintf(list, "</html>");
	fclose(list);
}

#endif /* HTML_H_ */
