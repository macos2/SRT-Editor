/*
 * MyTraceBar.h
 *
 *  Created on: 2021年1月2日
 *      Author: tom
 */

#ifndef UI_MYTRACEBAR_H_
#define UI_MYTRACEBAR_H_

#include <glib-object.h>
#include <glib.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS
#define MY_TYPE_TRACE_BAR my_trace_bar_get_type()
G_DECLARE_DERIVABLE_TYPE(MyTraceBar,my_trace_bar,MY,TRACE_BAR,GtkDrawingArea)

typedef struct _MyTraceBarClass{
	GtkDrawingAreaClass parent_class;
};

MyTraceBar *my_trace_bar_new(gchar *describe);

G_END_DECLS
#endif /* UI_MYTRACEBAR_H_ */
