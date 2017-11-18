#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
//#include "html.h"

int main(int argc, char* argv[]) {
	argv[1]="//home//evelina//inf//";
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (argv[1])) != NULL) {
	//if ((dir = opendir ("//home//evelina//")) != NULL) {

		FILE * html;
		html = fopen("html.txt","w");

		while ((ent = readdir (dir)) != NULL) {
		if((ent->d_name)[0] != '.'){ //without hidden files
			fprintf (html, "%s\n", ent->d_name);
		}
	  }

	  closedir (dir);
	} else {
	  perror ("");
	  return EXIT_FAILURE;
	}
}
