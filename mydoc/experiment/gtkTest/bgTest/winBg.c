#include   <gtk/gtk.h>  
#include   <stdlib.h>  
   
   
  GdkPixmap   *load_pixmap(GtkWidget   *widget,gchar   *filename)  
  {  
      GdkPixbuf   *pixbuf=NULL;  
      GdkPixmap   *pixmap=NULL;  
      pixbuf=gdk_pixbuf_new_from_file(filename,NULL);  
      if(!widget->window)printf("NULL\n");  
   
      pixmap=gdk_pixmap_new(widget->window,gdk_pixbuf_get_width(pixbuf),  
                                                                                gdk_pixbuf_get_height(pixbuf),-1);  
   
      gdk_pixbuf_render_to_drawable(pixbuf,pixmap,  
                                                                  widget->style->fg_gc[GTK_STATE_NORMAL],  
  0,0,0,0,  
  gdk_pixbuf_get_width(pixbuf),  
  gdk_pixbuf_get_height(pixbuf),  
  GDK_RGB_DITHER_NORMAL,0,0);  
   
   
      g_object_unref(pixbuf);  
      return   pixmap;  
  }  
   
  gboolean   set_widget_bg(gchar   *filename,GtkWidget   *widget)  
  {  
      GdkPixmap   *bg;  
      bg=load_pixmap(widget,filename);  
      gdk_window_set_back_pixmap(widget->window,bg,FALSE);  
      gdk_window_clear(widget->window);  
      return   TRUE;  
  }  
   
   
  int   main(int   argc,char*   argv[])  
  {  
      GtkWidget   *window,*fix   ;  
   
      gtk_init(&argc,&argv)   ;  
   
      window   =   gtk_window_new(GTK_WINDOW_TOPLEVEL)   ;  
      gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_main_quit),NULL)   ;  
   
   
      fix   =   gtk_fixed_new()   ;  
      gtk_container_add(GTK_CONTAINER(window),fix)   ;  
      set_widget_bg("bg1.jpg",fix)   ;  
   
      gtk_widget_show(fix)   ;  
   
      gtk_widget_show_all(window)   ;  
   
      gtk_main()   ;  
   
      return   0   ;  
       
  }   