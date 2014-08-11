/*http://www.linuxsir.org/bbs/showthread.php?t=274181
首先安装imagemagick软件包，其中的convert命令十分强大，可以把任意格式的图片文件转换为xpm文件格式。
假设有个test.bmp文件，我们可以用convert test.bmp test.xpm把它转换为xpm文件，因为Xlib默认支持的文件格式只有xpm所以我们只能这样做。得到的test.xpm实际是个文本文件，定义了的是一个字符串指针数组。
因为Xlib没有提供可以直接存取xpm文件的函数，所以我们还需要安装两个软件包libxpm4以及libxpm-dev。
然后写如下的代码

用gcc xpmtest1.c -o xpmtest -lX11 -lXpm

不好意思，这句应改为
rc = XpmCreatePixmapFromData(display, win, test, &pxmap, NULL, &xpmattr);


*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h> /* defines common Xlib functions and structs. */ 
#include <X11/xpm.h>
#include "test.xpm"


int main (int argc, char *argv[] )
{
	char *EnvDisp = NULL;
	/* this variable will contain the pointer to the Display structure */ 
	/* returned when opening a connection. */ 
	Display* display; 

	//处理DISPLAY环境变量
	if ( (EnvDisp = getenv("DISPLAY")) == NULL)
	{
		display = XOpenDisplay(":0.0"); 
	}
	else
	{
		display = XOpenDisplay(EnvDisp); 
	}
	if (display == NULL) { 
		fprintf(stderr, "Cannot connect to X server %s\n", EnvDisp?EnvDisp:"localhost:0.0"); 
		exit (-1); 
	} 
//检查SCREEN的属性
	/* this variable will be used to store the "default" screen of the */ 
	/* X server. usually an X server has only one screen, so we're only */ 
	/* interested in that screen. */ 
	int screen_num;
	/* these variables will store the size of the screen, in pixels. */ 
	int screen_width; 
	int screen_height; 
	/* this variable will be used to store the ID of the root window of our */ 
	/* screen. Each screen always has a root window that covers the whole */ 
	/* screen, and always exists. */ 
	Window root_window; 
	/* these variables will be used to store the IDs of the black and white */ 
	/* colors of the given screen. More on this will be explained later. */ 
	unsigned long white_pixel; 
	unsigned long black_pixel;
	/* check the number of the default screen for our X server. */ 
	screen_num = DefaultScreen(display); 
	/* find the width of the default screen of our X server, in pixels. */ 
	screen_width = DisplayWidth(display, screen_num);
	/* find the height of the default screen of our X server, in pixels. */ 
	screen_height = DisplayHeight(display, screen_num);
	/* find the ID of the root window of the screen. */ 
	root_window = RootWindow(display, screen_num);
	/* find the value of a white pixel on this screen. */ 
	white_pixel = WhitePixel(display, screen_num);
	/* find the value of a black pixel on this screen. */ 
	black_pixel = BlackPixel(display, screen_num); 
	
	fprintf(stdout, "Width x Height:%dx%d\n",
		screen_width, screen_height);
	Window win;
	int win_x = 0; 
	int win_y = 0;
	int win_border_width = 0;
	
	/* create the window, as specified earlier. */ 
	win = XCreateSimpleWindow(display, 
		root_window, 
		win_x, win_y, 
		screen_width, screen_height, 
		win_border_width, 
		black_pixel, 
		white_pixel); 
	
	XMapWindow(display, win); 
	
//加载相应的背景图片
	GC gc;
	XGCValues values ; 
	//values = CapButt | JoinBevel;
	unsigned long valuemask = GCCapStyle | GCJoinStyle;
	gc = XCreateGC(display, win, valuemask, &values);
	if( gc < 0)
	{
		fprintf(stderr, "GC can't be created\n");			
	}
	XSetForeground(display, gc,	black_pixel);
	XSetBackground(display, gc, white_pixel);

	Pixmap pxmap;
	XpmAttributes xpmattr;
	memset(&xpmattr, 0, sizeof(xpmattr));
	int rc;
	rc = XpmCreatePixmapFromData(display, win, test, &pxmap, NULL, &xpmattr);
	printf("XpmCreatePixmapFromData() return %d\n", rc);
	XCopyArea(display, pxmap, win, gc, 0, 0, xpmattr.width, xpmattr.height, 0, 0); 

//处理事件
	XSelectInput(display, win, ExposureMask | KeyReleaseMask);
	XEvent an_event;
	while(1)
	{
		XNextEvent(display, &an_event);
		switch( an_event.type)
		{
			case Expose:
				if( an_event.xexpose.count > 0)
					break;
				XCopyArea(display, pxmap, win, gc, 0, 0, xpmattr.width, xpmattr.height, 0, 0);
				break;
			case KeyRelease:
				printf("keycode %d\n", an_event.xkey.keycode);
				printf("keystate %d\n",an_event.xkey.state);
				break;				
			default:
				break;
		}
	}	

	XFreePixmap(display, pxmap);
	XCloseDisplay(display); 	

}
