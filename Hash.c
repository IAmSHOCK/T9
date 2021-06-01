#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Hash.h"

#define M 65536
#define MAXSIZE 256

list tab[M];

tipoObjeto *criar(char *v, int occur)
{
  tipoObjeto *obj;
  obj = (tipoObjeto *)malloc(sizeof(tipoObjeto));
  obj->valor = (char *)malloc(MAXSIZE * sizeof(char));
  strcpy(obj->valor, v);
  obj->ocorrencias = occur;
  return obj;
}

list create()
{
  list aux;
  aux = (list)malloc(sizeof(_STnode));
  if (aux != NULL)
  {
    aux->obj = NULL;
    aux->next = NULL;
  }
  return aux;
}

void procura_link(list l, tipoObjeto *obj, list *ant, list *atual)
{
  *ant = l;
  *atual = l->next;

  while ((*atual) != NULL && (*atual)->obj->ocorrencias > obj->ocorrencias)
  {
    *ant = *atual;
    *atual = (*atual)->next;
  }

  if ((*atual) != NULL && (*atual)->obj->ocorrencias != obj->ocorrencias)
  {
    *atual = NULL;
  }
}

void insert(list l, tipoObjeto *o)
{
  list no;
  list ant, atual;
  no = (list)malloc(sizeof(_STnode));
  if (no != NULL)
  {
    no->obj = o;
    procura_link(l, o, &ant, &atual);
    no->next = ant->next;
    ant->next = no;
  }
}

void procura_elimina(list l, tipoObjeto *obj, list *ant, list *atual)
{
  *ant = l;
  *atual = l->next;

  while ((*atual) != NULL && strcmp((*atual)->obj->valor, obj->valor) != 0)
  {
    *ant = *atual;
    *atual = (*atual)->next;
  }

  if ((*atual) != NULL && strcmp((*atual)->obj->valor, obj->valor) != 0)
  {
    *atual = NULL;
  }
}

void elimina(list l, tipoObjeto *o)
{
  list ant1;
  list atual1;
  procura_elimina(l, o, &ant1, &atual1);
  if (atual1 != NULL)
  {
    ant1->next = atual1->next;
    free(atual1);
  }
}

int codigo(char c)
{
  c = tolower(c);
  if (ispunct(c))
    c = '.';
  switch (c)
  {
  case 'a':
  case 'b':
  case 'c':
    return 2;
  case 'd':
  case 'e':
  case 'f':
    return 3;
  case 'g':
  case 'h':
  case 'i':
    return 4;
  case 'j':
  case 'k':
  case 'l':
    return 5;
  case 'm':
  case 'n':
  case 'o':
    return 6;
  case 'p':
  case 'q':
  case 'r':
  case 's':
    return 7;
  case 't':
  case 'u':
  case 'v':
    return 8;
  case 'w':
  case 'x':
  case 'y':
  case 'z':
    return 9;
  case '.':
    return 1;
  default:
    return -1;
  }
}

int codigo2(char *c)
{
  if (strcmp(c, "â") == 0)
    return 2;
  else if (strcmp(c, "ã") == 0)
    return 2;
  else if (strcmp(c, "á") == 0)
    return 2;
  else if (strcmp(c, "à") == 0)
    return 2;
  else if (strcmp(c, "ç") == 0)
    return 2;
  else if (strcmp(c, "é") == 0)
    return 3;
  else if (strcmp(c, "í") == 0)
    return 4;
  else if (strcmp(c, "õ") == 0)
    return 6;
  else if (strcmp(c, "ô") == 0)
    return 6;
  else if (strcmp(c, "Â") == 0)
    return 2;
  else if (strcmp(c, "Ã") == 0)
    return 2;
  else if (strcmp(c, "Á") == 0)
    return 2;
  else if (strcmp(c, "À") == 0)
    return 2;
  else if (strcmp(c, "Ç") == 0)
    return 2;
  else if (strcmp(c, "É") == 0)
    return 3;
  else if (strcmp(c, "Í") == 0)
    return 4;
  else if (strcmp(c, "Õ") == 0)
    return 6;
  else if (strcmp(c, "Ô") == 0)
    return 6;
  else if (strcmp(c, "ú") == 0)
    return 8;
  else if (strcmp(c,"Ú") == 0)
    return 8;
  else
    return -1;
}

int pont(char *v)
{
  for (int i = 0; i < strlen(v); i++)
  {
    unsigned char c = v[i];
    if (c < 128)
    {
      continue;
    }
    else
    {
      return i;
    }
  }
  return -1;
}

int completude(char *v)
{
  int p = pont(v);
  if (p == -1)
    return 5;
  else if (p <= 5)
    return 6;
  else
    return 5;
}

int hash(char *v)
{
  int n = strlen(v) - 1;
  if (strlen(v) > 6)
    n = completude(v);
  if (n >= strlen(v))
    n = strlen(v) - 1;
  //printf("tamanho n: %d\n", n);
  int j = 1;
  long unsigned int result = 0;
  for (int i = n; i >= 0; i--)
  {
    unsigned char c = v[i];
    if (c < 128)
    {
      result += codigo(v[i]) * j;
    }
    else
    {
      char t[2];
      t[1] = v[i--];
      t[0] = v[i];
      t[2] = '\0';
      result += codigo2(t) * j;
    }
    j *= 10;
  }
  //printf("%lu\n",result);
  return result % M;
}

void STinit()
{
  for (int h = 0; h < M; h++)
    tab[h] = create();
}

void STinsert(tipoObjeto *obj)
{
  char *v = obj->valor;
  int h = hash(v);
  list t;
  for (t = tab[h]->next; t != NULL; t = t->next)
    if (strcmp(t->obj->valor, v) == 0)
      break;

  if (t != NULL)
  {
    elimina(tab[h], obj);
    obj->ocorrencias++;
    insert(tab[h], obj);
  }
  else
  {
    obj->ocorrencias = 1;
    insert(tab[h], obj);
  }
}

tipoObjeto *STsearch(char *v)
{
  list t;
  int h = hash(v);
  for (t = tab[h]->next; t != NULL; t = t->next)
  {
    if (strcmp(t->obj->valor, v) == 0)
      break;
  }
  if (t != NULL)
    return t->obj;
  tipoObjeto *objetonulo = criar(v, 0);
  return objetonulo;
}

long long unsigned int clean(long long unsigned int hash)
{
  char str[25];
  sprintf(str, "%llu", hash);
  str[6] = '\0';
  long long unsigned int r = atoi(str);
  return r;
}

void imprimir(long long unsigned int h)
{
  long long unsigned int hashtmp = h;
  if (hashtmp > 1000000)
    hashtmp = clean(hashtmp);
  //printf("%llu\n",hashtmp);
  hashtmp = hashtmp % M;
  list t;
  int continuar = 0;
  for (t = tab[hashtmp]->next; t != NULL; t = t->next)
  {
    if (continuar == 0)
    {
      printf("%s %d\n", t->obj->valor, t->obj->ocorrencias);
    }
    else
    {
      break;
    }
    scanf("%d", &continuar);
  }
}

list get_link(long long unsigned int h)
{
  if (h > 1000000)
    h = clean(h);
  h = h % M;
  if(tab[h] == NULL) return NULL;
  return (tab[h]->next);
}

void addPunct()
{
  tipoObjeto *v = criar(",", 0);
  tipoObjeto *p = criar(".", 0);
  tipoObjeto *pv = criar(";", 0);
  tipoObjeto *e = criar("!", 0);
  tipoObjeto *i = criar("?", 0);
  tipoObjeto *d = criar(":", 0);
  tipoObjeto *ifen = criar("-", 0);

  STinsert(v);
  STinsert(p);
  STinsert(pv);
  STinsert(e);
  STinsert(i);
  STinsert(d);
  STinsert(ifen);
}

void copy(char str[], char *valor){
  for(int i=0; i<=strlen(valor); i++){
    str[i]=valor[i];
  }
}

void ficheiro(){
  FILE *f = fopen("dicionario.txt","w");
  for(int i=0; i<M; i++){
    list t;
    char str[128];
    for(t=tab[i]->next; t!=NULL; t=t->next){
      copy(str,t->obj->valor);
      fprintf(f, "%s %d\n", str, t->obj->ocorrencias);
    }
  }
  fclose(f);
}
