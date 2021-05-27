#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *vbox;
GtkWidget *button;
GtkWidget *label;

unsigned char button_str[30] = "2abcàáãâçABCÀÁÃÂÇ";

unsigned char caption[30]="";

int i = 0;
int j = 0;


GDateTime *LastPressed = NULL;

void button_clicked(GtkWidget *widget, gpointer data) {
  GTimeSpan diff;
  GDateTime *now = g_date_time_new_now_local();
  if (LastPressed != NULL)
  {
    diff = g_date_time_difference(now,LastPressed);

    if (diff < 1000000){
      	if (i<strlen(button_str)-1 && button_str[i]<128) i++;
      	else if (i<strlen(button_str)-2 && button_str[i]>127) i++;
	      else i=0;
    }
    else{
      i=0;
      j++;
    }
  }
  if (j > 0 && caption[j-1]>192){
    caption[j--] = 0;
    caption[j] = 0;
  }
  if (button_str[i]>127)
    {
      caption[j++] = button_str[i++];
      caption[j] = button_str[i];
    }
  else caption[j] = button_str[i];
  LastPressed = g_date_time_new_now_local();
  gtk_label_set_text((GtkLabel *) label, caption);
}

int main(int argc, char *argv[]) {

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 320);
  gtk_window_set_title(GTK_WINDOW(window), "T9 KEY");

  gtk_container_set_border_width(GTK_CONTAINER(window), 5);

  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
  label = gtk_label_new(NULL);
  button = gtk_button_new_with_label(button_str);
  gtk_container_add(GTK_CONTAINER(window),vbox);
  gtk_box_pack_start(GTK_BOX(vbox), label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(vbox), button,TRUE,TRUE,0);

  g_signal_connect(G_OBJECT(button), "clicked",
		   G_CALLBACK(button_clicked), NULL);

  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
