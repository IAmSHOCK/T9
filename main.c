#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Hash.h"
#include "gtk.h"


#define MAXSIZE 128
#define M 65536

int main (int argc, char *argv[]){
  FILE *f = fopen("lusiadas.txt", "r");
  STinit();
  char *str = (char*)malloc(MAXSIZE*sizeof(char));
  while(fgets(str, MAXSIZE, f) != NULL) {
    if(isdigit(str[0])){continue;}
    str[strlen(str)-1]='\0';
    char *token;
    token = strtok(str, " ");
    while(token != NULL) {
      //puts(token);
      if(ispunct(token[strlen(token)-1])) token[strlen(token)-1]='\0';
      tipoObjeto *tmp = STsearch(token);
      STinsert(tmp);
      token = strtok(NULL, " ");
    }
  }

  addPunct();

  printf("ready\n");
  gtk_inciar(argc, argv);
  long long unsigned int tmp;
  while(1){
    tmp = get_t9();
    imprimir(tmp);
  }
  return 0;
}
