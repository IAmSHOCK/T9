#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "Hash.h"

#define MAXSIZE 256
#define M 65536
#define ONOFF 12
#define SPACE 11
#define CYCLE 10
#define ON 1
#define OFF 0

GtkWidget *window;
GtkWidget *grid;
GtkWidget *button[13];
GtkWidget *console;

int dicionario;
link l;
link root;
long long unsigned int t9_result;

void set_label_empty(){
    gtk_label_set_text((GtkLabel *) console, " ");
}

void set_label(tipoObjeto *obj){
    if(obj != NULL)
        gtk_label_set_text((GtkLabel *) console, obj->valor);
}

void button_clicked(GtkWidget *widget, gpointer data)
{

    int *id = data;

    switch (*id)
    {
    case SPACE:
        l = NULL;
        root = NULL;
        t9_result = 0;
        set_label_empty();
        break;

    case CYCLE:
        l = (l->next == NULL) ? root : l->next;
        if (l->obj != NULL)
            set_label(l->obj);
        break;

    case ONOFF:
        dicionario = 0;
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

int main(int argc, char *argv[]) {
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
        char *token;
        token = strtok(str, " ");
        while (token != NULL)
        {
            //puts(token);
            if (ispunct(token[strlen(token) - 1]))
                token[strlen(token) - 1] = '\0';
            tipoObjeto *tmp = STsearch(token);
            STinsert(tmp);
            token = strtok(NULL, " ");
        }
    }

    addPunct();
    //fim do carregamento

    //gtk
    t9_result = 0;
    dicionario = ON;

    gchar *values[12] = {"1", "2 abc", "3 def", "4 ghi",
        "5 jkl", "6 mno","7 pqrs",
        "8 tuv", "9 wxyz", "cycle", "0 space", "on/off"
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

    return 0;
}




