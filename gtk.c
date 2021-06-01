#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "Hash.h"

#define MAXSIZE 256
#define M 65536
#define ONOFF 12
#define CLEAR 11
#define CYCLE 10
#define DEL 1
#define T9_ON 1
#define T9_OFF 0

GtkWidget *window;
GtkWidget *grid;
GtkWidget *button[13];
GtkWidget *console;
GDateTime *LastPressed = NULL;

unsigned char button_str[8][30] = { "abcàáãâçABCÀÁÃÂÇ", "defèéêDEFÈÉÊ", "ghiìíGHIÌÍ",
"jklJKL", "mnoòóõôMNOÒÓÕÔ",
"pqrsPQRS", "tuvùúTUVÙÚ", "wxyzWXYZ"
};
unsigned char caption[30]="";
int str_pos = 0;
int cap_pos = 0;

int dicionario;
list l;
list root;
long long unsigned int t9_result;
int used_key;

char *word;

char *dicio;
tipoObjeto *obj;

void set_label_empty(){
    gtk_label_set_text((GtkLabel *) console, " ");
}
void set_label_cycle(){
if (l != NULL && l->obj != NULL)
        gtk_label_set_text((GtkLabel *) console, l->obj->valor);
}
void set_label(){
    l = get_link(t9_result);
    root = l;
    if (l != NULL && l->obj != NULL){
        gtk_label_set_text((GtkLabel *) console, l->obj->valor);
        dicio=l->obj->valor;
    }
}

void use_keyboard(int key){
    key -= 2;
    if(key != used_key){
        str_pos = 0;
    }
    GTimeSpan diff;
    GDateTime *now = g_date_time_new_now_local();
    if (LastPressed != NULL)
    {
        diff = g_date_time_difference(now,LastPressed);

        if (diff < 500000){
            if (str_pos<strlen(button_str[key])-1 && button_str[key][str_pos]<128) str_pos++;
            else if (str_pos<strlen(button_str[key])-2 && button_str[key][str_pos]>127) str_pos++;
            else str_pos=0;
        }
        else{
        str_pos=0;
        cap_pos++;
        }
    }
    if (cap_pos > 0 && caption[cap_pos-1]>192){
        caption[cap_pos--] = 0;
        caption[cap_pos] = 0;
    }
    if (button_str[key][str_pos]>127)
        {
        caption[cap_pos++] = button_str[key][str_pos++];
        caption[cap_pos] = button_str[key][str_pos];
        }
    else caption[cap_pos] = button_str[key][str_pos];
    LastPressed = g_date_time_new_now_local();
    dicio=caption;
    gtk_label_set_text((GtkLabel *) console, caption);
}

void button_clicked(GtkWidget *widget, gpointer data)
{
    int *id = data;

    if(dicionario){

        switch (*id)
        {
            case DEL:
                if(t9_result < 10){
                    t9_result = 0;
                    set_label_empty();
                }
                else{
                    t9_result /= 10;
                    set_label();
                }
                break;
            case CLEAR:
                obj = STsearch(dicio);
                STinsert(obj);
                l = NULL;
                root = NULL;
                t9_result = 0;
                set_label_empty();
                break;

            case CYCLE:
                l = (l->next == NULL) ? root : l->next;
                set_label_cycle();
                break;

            case ONOFF:
                dicionario = (dicionario) ? T9_OFF : T9_ON;
                break;

            default:
                t9_result *= 10;
                t9_result += *id;
                l = get_link(t9_result);
                root = l;
                if (l != NULL && l->obj != NULL)
                    set_label(l->obj);
        }

    }

    else{
        switch (*id)
        {
            case DEL:
                //falta isto
                break;
            case CLEAR:
                obj = STsearch(dicio);
                STinsert(obj);
                cap_pos = 0;
                LastPressed = NULL;
                for (int i = 0; i < 30; i++)
                {
                    caption[i] = '\0';
                }

                set_label_empty();
                break;

            case CYCLE:
                break;

            case ONOFF:
                dicionario = (dicionario) ? T9_OFF : T9_ON;
                break;

            default:
                use_keyboard(*id);
                used_key = *id - 2;
        }
    }
}

void limpar(char *str){
  for(int i=0; i<strlen(str); i++){
    if(ispunct(str[i])) str[i]=' ';
  }
}

int main(int argc, char *argv[]) {
    FILE *dic = fopen("dicionario.txt","r");
    if(dic!=NULL){
      STinit();
      char *str = (char *)malloc(MAXSIZE * sizeof(char));
      while (fgets(str, MAXSIZE, dic) != NULL)
      {
          str[strlen(str) - 1] = '\0';
          char *string = (char *)malloc(MAXSIZE * sizeof(char));

          char *token;
          token = strtok(str, " ");
          strcpy(string,token);
          token = strtok(NULL, " ");
          int freq = atoi(token);

          tipoObjeto *tmp = STsearch(string);
          for(int i=0; i<freq; i++){
            STinsert(tmp);
          }
      }
      fclose(dic);
    }
    else{
      //carregar dicionario
      FILE *f = fopen("lusiadas.txt", "r");
      STinit();
      char *str = (char *)malloc(MAXSIZE * sizeof(char));
      while (fgets(str, MAXSIZE, f) != NULL)
      {
          if (isdigit(str[0]))
          {
              continue;
          }
          str[strlen(str) - 1] = '\0';
          limpar(str);
          char *token;
          token = strtok(str, " ");
          while (token != NULL)
          {
              //puts(token);
              tipoObjeto *tmp = STsearch(token);
              STinsert(tmp);
              token = strtok(NULL, " ");
          }
      }
      fclose(f);
      addPunct();
    }
    //fim do carregamento

    //gtk
    t9_result = 0;
    dicionario = T9_ON;

    gchar *values[12] = {"DEL", "2 abc", "3 def", "4 ghi",
        "5 jkl", "6 mno","7 pqrs",
        "8 tuv", "9 wxyz", "CYCLE", "CLEAR", "ON/OFF"
    };

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    //gtk_window_set_default_size(GTK_WINDOW(window), 250, 180);
    gtk_window_set_default_size(GTK_WINDOW(window), 150, 200);
    gtk_window_set_title(GTK_WINDOW(window), "GtkGrid");
    gtk_container_set_border_width(GTK_CONTAINER(window), 1);
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 1);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 1);
    int i = 0;
    int j = 0;
    int pos= 0;
    int tmp = 1;
    int button_counter[13];
    for (i=80; i < 84; i++) {
        for (j=30; j < 33; j++) {
            button_counter[tmp] = tmp;
            button[tmp]= gtk_button_new_with_label(values[pos]);
            g_signal_connect(G_OBJECT(button[tmp]), "clicked", G_CALLBACK(button_clicked), &button_counter[tmp]);
            gtk_grid_attach(GTK_GRID(grid), button[tmp], j, i, 1, 1);
            pos++;
            tmp++;
        }
    }

    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

    //consola
    console = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), console, 0, 0, 50, 40);

    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_show_all(window);
    gtk_main();
    ficheiro();
    return 0;
}
