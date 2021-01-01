/*
 * MainWin.h
 *
 *  Created on: 2019年11月21日
 *      Author: tom
 */

#ifndef MAINWIN_H_
#define MAINWIN_H_

#include <cairo.h>
#include <gtk/gtk.h>
#include <gst/gst.h>
#include "SubTitle.h"

G_BEGIN_DECLS
#define MY_TYPE_MAIN_WIN my_main_win_get_type()
G_DECLARE_DERIVABLE_TYPE(MyMainWin,my_main_win,MY,MAIN_WIN,GtkWindow);
typedef struct _MyMainWinClass{
	GtkWindowClass Parent_class;
};

MyMainWin *my_main_win_new(gchar *title,gchar *uri,gboolean play);
G_END_DECLS
#endif /* MAINWIN_H_ */
