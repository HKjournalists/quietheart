/*本程序功能：
 *获取并打印窗口的常用属性：父窗口，根窗口，窗口大小，坐标
 * */
#include <stdio.h>

/*exit, getenv*/
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

/*创建一个窗口的函数*/
Window
create_simple_window(Display* display, int width, int height, int x, int y);

void setWinProp(Display *display, Window win);
void getWinProp(Display *display, Window win);
int main(int argc, char *argv[])
{
	Display* display;
	int screen_num;
	Window win;
	unsigned int display_width,
				 display_height;
	unsigned int win_width,
				 win_height;

	/**********************初始化相关*****************/
	char *display_name = getenv("DISPLAY"); 
	display = XOpenDisplay(display_name);
	if (display == NULL)
	{
		fprintf(stderr, "%s: cannot connect to X server '%s'\n",
				argv[0], display_name);
		exit(1);
	}
	/*************************************************/

	/********************创建一个窗口*****************/
	screen_num = DefaultScreen(display);
	display_width = DisplayWidth(display, screen_num);
	display_height = DisplayHeight(display, screen_num);

	win_width = (display_width / 3);
	win_height = (display_height / 3);
	printf("set the width of the window:%d\n", win_width);
	printf("set the height of the window:%d\n", win_height);

	win = create_simple_window(display, win_width, win_height, 0, 0);
	/*************************************************/

	/******************设置窗口的常用属性*****/
    setWinProp(display, win);
	/*************************************************/

	/******************这里开始获取窗口的常用属性*****/
    getWinProp(display, win);

	/*************************************************/
	sleep(25);
	XCloseDisplay(display);
	return 0;
}
Window
create_simple_window(Display* display, int width, int height, int x, int y)
{


  int screen_num = DefaultScreen(display);


  int win_border_width = 2;

  Window win;

  win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
                            x, y, width, height, win_border_width,
                            BlackPixel(display, screen_num),
                            WhitePixel(display, screen_num));

  

  XSetTransientForHint(display, win, RootWindow(display, screen_num));

  XMapWindow(display, win);

  XFlush(display);

  return win;
}
void setWinProp(Display *display, Window win)
{
	XTextProperty window_name_property;
    XTextProperty icon_name_property;
    XSizeHints* win_size_hints;
    XWMHints* win_hints;
    Pixmap icon_pixmap;
    char* window_name = "hello, world";
    char* icon_name = "small world";

    int rc = XStringListToTextProperty(&window_name,
                                       1,
                                       &window_name_property);
    if (rc == 0)
	{
        fprintf(stderr, "XStringListToTextProperty - out of memory\n");
        exit(1);
    }

    rc = XStringListToTextProperty(&icon_name,
                                   1,
                                   &icon_name_property);
    if (rc == 0)
	{
        fprintf(stderr, "XStringListToTextProperty - out of memory\n");
        exit(1);
    }
	XSetWMName(display, win, &window_name_property);
    XSetWMIconName(display, win, &icon_name_property);

    win_size_hints = XAllocSizeHints();
    if (!win_size_hints)
	{
        fprintf(stderr, "XAllocSizeHints - out of memory\n");
        exit(1);
    }
    win_size_hints->flags = PSize | PMinSize;
    win_size_hints->min_width = 300;
    win_size_hints->min_height = 200;
    win_size_hints->base_width = 400;
    win_size_hints->base_height = 250;
    XSetWMNormalHints(display, win, win_size_hints);

    XFree(win_size_hints);
	XFlush(display);

}

void getWinProp(Display *display, Window win)
{
	/*获取窗口属性*/
	/*相对于根窗口的坐标*/
	int screen_x;
	int screen_y;

	/*窗口的宽度和高度*/
	unsigned int win_width,
				 win_height;

	/*相对于父窗口的坐标*/
	int win_x,
		win_y;

	/*窗口边缘宽度*/
	int win_border_width;

	/*根窗口*/
	Window win_root;

	/*父窗口*/
	Window win_parent;

	/*子窗口列表*/
	Window* win_children;

	/*子窗口数目*/
	int child_win_num;

	/*一个和win转换后坐标相同坐标的转换坐标对应窗口的子窗口*/
	Window child_win;

	/*初始化变量*/
	win_width = 0;
	win_height = 0;
	win_border_width = 0;
	win_root = 0;
	child_win_num = 0;
	win_x = 0;
	win_y = 0;
	XWindowAttributes win_attr;

	/*获取窗口的属性*/
	Status rc = XGetWindowAttributes(display, win, &win_attr);

	win_width = win_attr.width;
	win_height = win_attr.height;

	/*注意这里的窗口坐标是相对于父窗口的坐标*/
	win_x = win_attr.x;
	win_y = win_attr.y;

	win_border_width = win_attr.border_width;
	//win_root = win_attr.root;
	//printf("the root winID of win before is: %d\n", win_root);

	/*获得窗口win的层次
	 *win_root:存放获取的根窗口
	 *win_parent:存放获取的父窗口
	 *win_children:存放子窗口列表(由底向上)
	 *child_win_num:存放子窗口数目
	 * */
	XQueryTree(display, win,
			&win_root,
			&win_parent,
			&win_children, &child_win_num);
	XFree(win_children);

	/*把相对win_parent的坐标转换为对于win_root的坐标
	 *win_parent：源窗口（这里就是父窗口）
	 *win_root:目标窗口
	 *win_attr.x,win_attr.y:相对于源窗口的坐标
	 *screen_x,screen_y：存放转换后相对于目标窗口的坐标
	 *child_win:是目标窗口的一个子窗口，这个子窗口的坐标也是转换后的坐标,
	 如果没有这样的窗口则设置为none.
	 *如果返回TRUE,那么转换成功，否则说明win_parent和win_root在不同的屏幕上，
	 所以screen_x/y都是0.
	 *
	 * */
	XTranslateCoordinates(display, win_parent, win_root,
			win_attr.x, win_attr.y, &screen_x, &screen_y,
			&child_win);


	printf("the width of win is: %d\n", win_width);
	printf("the height of win is: %d\n", win_height);
	printf("the relative x coordinate of win is: %d\n", win_x);
	printf("the relative y coordinate of win is: %d\n", win_y);
	printf("the translated x coordinate of win: %d\n", screen_x);
	printf("the translated y coordinate of win: %d\n", screen_y);
	printf("the border width of win is: %d\n", win_border_width);
	printf("the root winID of win is: %d\n", win_root);
	printf("the parent winID of win is: %d\n", win_parent);
	printf("the winID of win is: 0x%x\n", win);

	/*我尝试之后发现这个child窗口是顶部面板的窗口,而顶部窗口的坐标也是这个*/
	printf("winID of one root win child has the same translated coordinate is: 0x%x\n", child_win);

	printf("the the number of child win is: %d\n", child_win_num);
}
