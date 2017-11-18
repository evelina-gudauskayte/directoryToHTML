#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "html.h"

int main(int argc, char* argv[]) {
	argv[1]="//home//evelina//inf//";
	//*argv[2]='1'; //with hidden files
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (argv[1])) != NULL) {

		FILE * html;
		html = fopen("html","w");
		htmlBEGIN(html);
		htmlHEAD( html, argv[1]);
		while ((ent = readdir (dir)) != NULL) {
			if((*argv[2])!='1'){
				if((ent->d_name)[0] != '.'){ //without hidden files
					htmlTEXT (html,ent->d_name);
				}
			}else{
				fprintf (html, "%s\n", ent->d_name); //with hidden files
			}
	  }
		htmlEND(html);
		closedir (dir);
		fclose(html);

	} else {
	  perror ("");
	  return EXIT_FAILURE;
	}

}
