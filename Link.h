#ifndef LINK_H_INCLUDED
#define LINK_H_INCLUDED

#include "Hash.h"

typedef struct STnode* link;
typedef struct STnode {
  tipoObjeto obj;
  link next;
}_STnode;


link inic ();
void elimina(link l, tipoObjeto o);
void insere (link l, tipoObjeto o);

#endif // LINK_H_INCLUDED
