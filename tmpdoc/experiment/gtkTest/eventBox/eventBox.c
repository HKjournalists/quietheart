#include<gtk/gtk.h>
gint
main (gint argc, gchar *argv[])
{

  GtkWidget *window;
  GtkWidget *eventBox;
  GtkWidget *image;
  GdkColor color;
  gtk_init(&argc, &argv);
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  //gtk_window_set_default_size(GTK_WINDOW(window), 800, 480); 
  gdk_color_parse("green", &color);
  gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);
  eventBox = gtk_event_box_new();
  gtk_widget_set_events (eventBox, GDK_BUTTON_PRESS_MASK);

  g_signal_connect (G_OBJECT (eventBox), "button_press_event",
	              G_CALLBACK (gtk_main_quit), NULL);

  gtk_container_add(GTK_CONTAINER(window), eventBox);

  image = gtk_image_new_from_file("image.png");
  gtk_container_add(GTK_CONTAINER(eventBox), image);
  
  gtk_widget_show_all(window);

  gtk_main();
  return 0;
}


