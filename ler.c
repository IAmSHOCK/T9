#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 128

int main(){
    FILE *f = fopen("lusiadas.txt", "r");
    if(f==NULL) printf("Cannot open");
    char *str = (char*)malloc(MAXSIZE*sizeof(char));
    char *tmp = (char*)malloc(MAXSIZE*sizeof(char));
    int ind =0;
    while(fgets(str, MAXSIZE, f) != NULL){
        if(str[strlen(str)-1]=='\n') str[strlen(str)-1]='\0';
        for(int i=0; i<strlen(str); i++){
            if(isalpha(str[i])){
                tmp[ind++]=str[i];
            }
            else if(ispunct(str[i])){
                tmp[ind++]='\0';
                printf("%s",tmp);
                ind=0;
                free(tmp);
                tmp = (char*)malloc(MAXSIZE*sizeof(char));
                tmp[ind++]=str[i];
                tmp[ind++]='\0';
                printf("%s",tmp);
                ind=0;
                free(tmp);
                tmp = (char*)malloc(MAXSIZE*sizeof(char));

            }
            else if (str[i]==' ' || str[i]=='\n'){
                tmp[ind++]='\0';
                printf("%s", tmp);
                ind=0;
                free(tmp);
                tmp = (char*)malloc(MAXSIZE*sizeof(char));
            }
        }
    }
}
