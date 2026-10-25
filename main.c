#include <X11/Xlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdlib.h>
#include "config.h"
#define clear() system("clear")
#define newline() puts("")
#define dnewline() puts("\n")
#define ALT_KEY ALTERNATIVE_KEY
#define WIN_KEY PRIMARY_KEY
#define key(x) XStringToKeysym(x)
#define BUTTON_PRESS ButtonPressMask|ButtonReleaseMask|PointerMotionMask
#define errquit() exit(1);
#define ERROR stderr
#define OVERLAP_KEY 	overlapping_key
#define KILL_KEY    	killing_key
#define LAUNCHER_KEY    launching_key
void logo() {
	puts("\033[96m||   ||   ||\033[0m      Welcome to  ");
	puts("\033[96m||   ||   ||\033[0m      Water WM    ");
	puts("\033[96m||| ||||  ||\033[0m      A WM thats  ");
	puts("\033[96m  || || ||  \033[0m      liquid >:D");
	puts("\033[92m..............................\033[0m");
}
void intro() {
	clear();
	logo();
	dnewline();
}
void dbgtext(FILE* where, char* text) {
	fprintf(where, "[\033[95mDEBUG\033[0m] info: %s\n", text);
}
void notetext(char* text) {
	printf("\033[93mnote\033[0m: %s\n", text);
}
void nodpyerr(void) {
	dbgtext(ERROR, "Couldn't use the X Display :/");
	notetext("You maybe could set display to :0 via export DISPLAY=:0, if that still doesn't work, wrap WaterWM in an .xinitrc :3");
	errquit();
}
void forkerr(void) {
	dbgtext(ERROR, "Couldn't fork (thats weird, tbh)");
	notetext("Maybe you've reached PID_MAX or you are out of memory? That's rough, we're in the worst times to buy RAM...");
	errquit();
}
void execveerr(void) {
	dbgtext(ERROR, "Couldn't execve... why though?");
	errquit();
}
int main(int argc, char** argv) {
	for (int i=0; i<argc; i++) {
		if (!strcmp(argv[i], "nointro")) showintro = false;
	}
	if (showintro) intro();
	
	XEvent ev;
	XButtonEvent start;
	XWindowAttributes attr;
	Display *dpy = XOpenDisplay(NULL);
	if (!dpy) nodpyerr();
	XGrabButton(dpy, 1, WIN_KEY, DefaultRootWindow(dpy), True, BUTTON_PRESS, GrabModeAsync, GrabModeAsync, None, None);
	XGrabButton(dpy, 3, WIN_KEY, DefaultRootWindow(dpy), True, BUTTON_PRESS, GrabModeAsync, GrabModeAsync, None, None);
	XGrabKey(dpy, XKeysymToKeycode(dpy, key(OVERLAP_KEY)), WIN_KEY, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XKeysymToKeycode(dpy, key(KILL_KEY)), WIN_KEY, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XKeysymToKeycode(dpy, key(LAUNCHER_KEY)), WIN_KEY, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
	start.subwindow = None;
	system(keymapcmd);
	for (;;) {
		XNextEvent(dpy, &ev);
		if (ev.type == KeyPress && ev.xkey.subwindow != None) {
			if (ev.xkey.keycode == XKeysymToKeycode(dpy, key(OVERLAP_KEY)) && ev.xkey.state & WIN_KEY) XRaiseWindow(dpy, ev.xkey.subwindow);
		}
		 if (ev.type == KeyPress) {
			if (ev.xkey.keycode == XKeysymToKeycode(dpy, key(KILL_KEY)) && ev.xkey.state & WIN_KEY) system(killcmd);
			if (ev.xkey.keycode == XKeysymToKeycode(dpy, key(LAUNCHER_KEY)) && ev.xkey.state & WIN_KEY) system(launchercmd);
		} else if (ev.type == ButtonPress && ev.xbutton.subwindow != None) {
			XGetWindowAttributes(dpy, ev.xbutton.subwindow, &attr);
			start = ev.xbutton;
		} else if (ev.type == MotionNotify && start.subwindow != None) {
			int Ofydf = ev.xbutton.x_root - start.x_root;
			int Ofxdf = ev.xbutton.y_root - start.y_root;
			#define maximium(a, b) ((a) > (b) ? (a) : (b))
			XMoveResizeWindow(dpy, start.subwindow,
				attr.x + (start.button==1 ? Ofydf : 0),
				attr.y + (start.button==1 ? Ofxdf : 0),
				maximium(1, attr.width + (start.button==3 ? Ofydf : 0)),
				maximium(1, attr.height + (start.button==3 ? Ofxdf : 0)));
		} else if (ev.type == ButtonRelease) start.subwindow = None;
	}
}
