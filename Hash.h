#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

typedef struct {
  int ocorrencias;
  char *valor;
}tipoObjeto;

typedef struct STnode* list;
typedef struct STnode {
  tipoObjeto *obj;
  list next;
}_STnode;

tipoObjeto* criar (char *v, int oco);
list create();
int hash(char *v);
void STinit();
void STinsert(tipoObjeto *obj);
tipoObjeto* STsearch(char *v);
void imprimir(long long unsigned int h);
void insert (list l, tipoObjeto *obj);
void elimina (list l, tipoObjeto *o);
list get_link(long long unsigned int h);
void addPunct();
#endif // HASH_H_INCLUDED
