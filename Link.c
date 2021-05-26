#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Hash.h"
#include "Link.h"

link inic (){
    link aux;
    aux = (link) malloc (sizeof(_STnode));
    aux=NULL;
    return aux;
}

void procura_lista_ele(link l, char *str, link *ant, link *atual){
    *ant= l;
    *atual= l->next;
    while ((*atual) != NULL  && strcmp((*atual)->obj.valor, str)!=0) {
        *ant= *atual;
        *atual= (*atual)->next;
    }
    if ((*atual) != NULL && strcmp((*atual)->obj.valor, str)!=0)
        *atual= NULL;   /* Se elementon nao encontrado*/
}


void elimina(link l, tipoObjeto o){
    link ant1;
    link atual1;
    procura_lista_ele(l, o.valor, &ant1, &atual1);
    if (atual1 != NULL) {
        ant1->next = atual1->next;
        free (atual1);
    }
}

void procura_lista(link l, tipoObjeto o, link *ant, link *atual){
    *ant= l;
    *atual= l->next;
    while ((*atual) != NULL  && (*atual)->obj.ocorrencias > o.ocorrencias) {
        *ant= *atual;
        *atual= (*atual)->next;
    }
    if ((*atual) != NULL && strcmp((*atual)->obj.valor, o.valor)!=0)
        *atual= NULL;   /* Se elemento nao encontrado*/
}

void insere (link l, tipoObjeto o){
    link no;
    link ant, atual;
    no = (link) malloc (sizeof(_STnode));
    if (no != NULL) {
        no->obj = o;
        procura_lista(l, o, &ant, &atual);
        no->next = ant->next;
        ant->next = no;
    }
}
