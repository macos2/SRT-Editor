/*
 * main.c
 *
 *  Created on: 2019年11月21日
 *      Author: tom
 */
#include <gtk/gtk.h>
#include <gst/gst.h>
#include "UI/MainWin.h"

int main(int argc,char *argv[]){
	gtk_init(&argc,&argv);
	gst_init(&argc,&argv);
	MyMainWin *m=my_main_win_new(NULL,"file:///home/tom/eclipse-workspace/Spring.mp4",TRUE);
	gtk_widget_show_all(m);
	gtk_main();
	return EXIT_SUCCESS;
}
