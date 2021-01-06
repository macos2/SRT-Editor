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
	void (*obj_active)(MyTraceBar *self,gpointer obj);
	void (*obj_selected)(MyTraceBar *self,gpointer obj);
	void (*obj_range_change)(MyTraceBar *self,gpointer obj,gfloat start,gfloat end);
	void (*obj_describe_change)(MyTraceBar *self,gpointer obj,gchar *new_describe);
	void (*obj_color_change)(MyTraceBar *self,gpointer obj,GdkRGBA *color);
};

MyTraceBar *my_trace_bar_new(gchar *describe);
gdouble my_trace_bar_get_value(MyTraceBar *bar);
void my_trace_bar_set_value(MyTraceBar *bar,gdouble value);
const gchar* my_trace_bar_get_describe(MyTraceBar *bar);

void my_trace_bar_add_obj_range(MyTraceBar *bar,gpointer obj,gdouble start,gdouble end,const gchar *describe,const GdkRGBA *color);
void my_trace_bar_del_obj_range(MyTraceBar *bar,gpointer obj);
const gchar* my_trace_bar_get_obj_describe(MyTraceBar *bar,gpointer obj);
void my_trace_bar_set_obj_describe(MyTraceBar *bar,gpointer obj,const gchar *describe);
void my_trace_bar_get_obj_range(MyTraceBar *bar,gpointer obj,gdouble *min,gdouble *max);
void my_trace_bar_set_obj_range(MyTraceBar *bar,gpointer obj,const gdouble min,const gdouble max);
const GdkRGBA *my_trace_bar_get_obj_color(MyTraceBar *bar,gpointer obj);
void my_trace_bar_set_obj_color(MyTraceBar *bar,gpointer obj,const GdkRGBA *color);


G_END_DECLS
#endif /* UI_MYTRACEBAR_H_ */
