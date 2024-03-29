// XsendEvent utility

#include <unistd.h> 
#include <X11/Xlib.h> 
#include <X11/Xutil.h> 
using namespace std;

void mouseClick(int button) { 
Display *display = XOpenDisplay(NULL); 
  XEvent event; 
  if(display == NULL) 
  {
    cout << "clicking error 0" << endl; 
    exit(EXIT FAILURE);
  }

memset(&event, 0x00, sizeof(event)); 
  
event.type = ButtonPress; 
event.xbutton.button = button; 
event.xbutton.same_screen = True; 

  
XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state); 
event.xbutton.subwindow = event.xbutton.window; 

  
  while(event.xbutton.subwindow) 
  {
    event.xbutton.window = event.xbutton.subwindow; 
    XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state); 
} 
if(XSendEvent(display, PointerWindow, True, Oxfff, &event) == 0) 
{cout << "clicking error 1" << endl;} 
  
  XFlush(display); 
  
  event.type = ButtonRelease;
  event.xbutton.state = Ox100; 
  
  if(XSendEvent(display, PointerWindow, True, Oxfff, &event) == 0) 
    cout << "clicking error 2" << endl; 
  
  XFlush(display);
  XCloseDisplay(display); 
}

//Part 2 Chrome Compatible

#include <X11/extensions/XTest.h> 

void SendClick(int button, Bool down) { 
Display *display = XOpenDisplay(NULL); 
XTestFakeButtonEvent(display, button, down, CurrentTime); 
XFlush(display); 
XCloseDisplay(display); 
} 


//Part 3 Calling the function
//You Need add-lX11 -lXtst libs to compile

//XSendEvent variant
mousClick(1);

//XTestFakeButtonEvent variant
SendClick (1, true);   //press lmb
SendClick(1, false);  //release lmb
