#include   <gtk/gtk.h>  
#include   <stdlib.h>  

/*static gboolean
window_expose_event (GtkWidget      *widget,
                     GdkEventExpose *event)
{
      GdkPixbuf   *pixbuf=NULL;  
      GdkPixmap   *pixmap=NULL;
      pixbuf=gdk_pixbuf_new_from_file("./tvButton.png",NULL);//加载文件到缓存
	pixmap=gdk_pixmap_new(widget->window,gdk_pixbuf_get_width(pixbuf),gdk_pixbuf_get_height(pixbuf),-1);//设置显示图形的区域
     gdk_pixbuf_render_to_drawable(pixbuf,pixmap,
widget->style->bg_gc[GTK_STATE_NORMAL],  
0,0,0,0,  
gdk_pixbuf_get_width(pixbuf),  
gdk_pixbuf_get_height(pixbuf),  
GDK_RGB_DITHER_NORMAL,0,0);  //把图形提交到区域中去,倒数第4，5个都设为-1即可
     g_object_unref(pixbuf);
     gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);
     return FALSE;
}*/


int   main(int   argc,char*   argv[])  
  {  
      GtkWidget   *window,*fix;  
  	GdkPixbuf   *pixbuf=NULL;  
      GdkPixmap   *pixmap=NULL;
	GtkStyle *style;  
	//GtkWidget *fixed;
      gtk_init(&argc,&argv)   ;  
   	
	
      window   =   gtk_window_new(GTK_WINDOW_TOPLEVEL); 
      gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_main_quit),NULL)   ;  

//fixed = gtk_fixed_new();
//gtk_fixed_set_has_window (GTK_FIXED(fixed), TRUE);
//gtk_container_add(GTK_CONTAINER (window), fixed);
	gtk_window_set_default_size(GTK_WINDOW(window), 100, 200);
	gtk_widget_set_app_paintable(window,TRUE);
      pixbuf=gdk_pixbuf_new_from_file("./tvButton.png",NULL);//加载文件到缓存
	pixmap=gdk_pixmap_new(window->window,gdk_pixbuf_get_width(pixbuf),gdk_pixbuf_get_height(pixbuf),-1);//设置显示图形的区域



     /*gdk_pixbuf_render_to_drawable(pixbuf,pixmap,
window->style->fg_gc[GTK_STATE_NORMAL],  
0,0,0,0,  
gdk_pixbuf_get_width(pixbuf),  
gdk_pixbuf_get_height(pixbuf),  
GDK_RGB_DITHER_NORMAL,0,0);  //把图形提交到区域中去,倒数第4，5个都设为-1即可
g_object_unref(pixbuf);*/
/**/
	/*gdk_draw_pixbuf(pixmap, window->style->bg_gc[GTK_STATE_NORMAL],
pixbuf, 0,0,0,0,-1,-1,GDK_RGB_DITHER_NORMAL,0,0);*/

gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, NULL, 0);
gdk_pixbuf_render_threshold_alpha   (pixbuf,pixmap,0,0,0,0,-1,-1,128);
	/*style = gtk_style_copy(window->style);

	if (style->bg_pixmap[GTK_STATE_NORMAL])
		g_object_unref(style->bg_pixmap[GTK_STATE_NORMAL]);

	style->bg_pixmap[GTK_STATE_NORMAL] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_ACTIVE] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_PRELIGHT] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_SELECTED] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_INSENSITIVE] = g_object_ref(pixmap);

	gtk_widget_set_style(window, style);
	g_object_unref(style);*/

 //gdk_window_set_back_pixmap(window->window, pixmap, FALSE);

      /*fix   =   gtk_fixed_new()   ;  
      gtk_container_add(GTK_CONTAINER(window),fix)   ;  
      set_widget_bg("bg1.jpg",fix)   ;  
   
      gtk_widget_show(fix)   ; */ 
         gtk_widget_show_all(window)   ;  
gdk_window_clear(window->window);
   /*g_signal_connect_after (window, "expose-event",
                          G_CALLBACK (window_expose_event), NULL);*/
      gtk_main()   ;  
   
      return   0   ;  
       
  }   
