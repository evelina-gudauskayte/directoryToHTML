/*
 * html.c
 *
 *  Created on: 14.11.2017
 *      Author: evelina
 */
#include <stdio.h>
#include "html.h"

void htmlBEGIN(FILE* html){
	fprintf(html,"<html>");
}

void htmlEND(FILE* html){
	fprintf(html,"</html>");
}

void htmlHEAD(FILE* html, char* title){
	fprintf(html, "\n \v <head> \n \v \v <h1>");
	fprintf(html, "%s" , title);
	fprintf(html, " \n \v \v </h1> \n \v </head> \n");
}

void htmlTEXT(FILE* html, char* text){
	fprintf(html, "<p> %s </p>", text);
}
