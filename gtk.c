
#include <stdio.h>
#include "gtk.h"
#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *grid;
GtkWidget *button[13];

GtkWidget *console;
GtkWidget *vbox;
GtkWidget *console_button;

long long unsigned int t9_result;

void button_clicked(GtkWidget *widget, gpointer data) {
    int *id = data;
    if(*id == 11){
        t9_result = 0;
    }
    else{

        t9_result *= 10;
        t9_result += *id;
    }
    
    g_print("%llu\n", t9_result);
}

long long unsigned int get_t9(){
    return t9_result;
}

void gtk_inciar(int argc, char *argv[]) {
    
    t9_result = 0;

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
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    console = gtk_label_new("Teste");
    gtk_grid_attach(GTK_GRID(grid), console, 0, 0, 50, 40);    
    //

    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_show_all(window);
    gtk_main();

}




