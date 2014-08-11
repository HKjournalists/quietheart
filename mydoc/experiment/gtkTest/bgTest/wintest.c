

#include   <gtk/gtk.h>  
#include   <stdlib.h>  

void update_widget_bg(GtkWidget *widget, gchar *img_file)
{
        GtkStyle *style;
        GdkPixbuf *pixbuf;
        GdkPixmap *pixmap;

        gint width, height;
        
        pixbuf = gdk_pixbuf_new_from_file(img_file, NULL);

        width = gdk_pixbuf_get_width(pixbuf);
        height = gdk_pixbuf_get_height(pixbuf);

        pixmap = gdk_pixmap_new(NULL, width, height, 24);
        gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, NULL, 0);

	style = gtk_style_copy(GTK_WIDGET (widget)->style);

	if (style->bg_pixmap[GTK_STATE_NORMAL])
		g_object_unref(style->bg_pixmap[GTK_STATE_NORMAL]);

	style->bg_pixmap[GTK_STATE_NORMAL] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_ACTIVE] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_PRELIGHT] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_SELECTED] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_INSENSITIVE] = g_object_ref(pixmap);

	gtk_widget_set_style(GTK_WIDGET (widget), style);//替代了
	//gtk_widget_modify_style(GTK_WIDGET (widget), style);//直接改，但是style类型不同了
	g_object_unref(style);
}
int   main(int   argc,char*   argv[])  
  {  
      GtkWidget   *window,*fix   ;  
  	GdkPixbuf   *pixbuf=NULL;  
      GdkPixmap   *pixmap=NULL;  
	//GtkWidget *fixed;
      gtk_init(&argc,&argv)   ;  
   	
	
      window   =   gtk_window_new(GTK_WINDOW_TOPLEVEL); 
      gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_main_quit),NULL)   ;  

update_widget_bg(window, "./tvButton.png");
   
      gtk_widget_show_all(window)   ;  
   
      gtk_main()   ;  
   
      return   0   ;  
       
  }   
