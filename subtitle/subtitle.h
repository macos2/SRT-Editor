/*
 * subtitle.h
 *
 *  Created on: 2021年1月8日
 *      Author: tom
 */

#ifndef SUBTITLE_SUBTITLE_H_
#define SUBTITLE_SUBTITLE_H_
#include <glib.h>
#include <glib-object.h>
#include <cairo.h>
#include <pango/pango.h>
#include "gtk/gtk.h"
G_BEGIN_DECLS
#define MY_TYPE_SUBTITLE my_subtitle_get_type()
G_DECLARE_INTERFACE(MySubtitle,my_subtitle,MY,SUBTITLE,GObject);

typedef enum{
	Subtitle_Format_None = 0,
	Subtitle_Format_Bold = 0x01<<0,
	Subtitle_Format_Itatic = 0x01 << 1,
	Subtitle_Format_Underline = 0x01 << 2,
	Subtitle_Format_Special_Color = 0x01 << 3,
	Subtitle_Format_Special_Font=0x01 << 4,
	Subtitle_Format_Position=0x01 << 5,
	Subtitle_Format_Images=0x01<<6,
}SubtitleFormat;

typedef struct _MySubtitleInterface{
GTypeInterface parent_iface;
guint64 (*add_subtitle)(MySubtitle *self,gchar *text,gdouble start,gdouble end,va_list ap);
void (*del_subtitle)(MySubtitle *self,guint64 index);
gchar *(*to_string)(MySubtitle *self);
gboolean (*to_file)(MySubtitle *self,gchar *location);
void (*load_file)(MySubtitle *self,gchar *location);
gchar *(*get_subtitle)(MySubtitle *self,guint64 index,gdouble *start,gdouble *end,va_list ap);
guint64 (*get_total_size)(MySubtitle *self);
};

guint64 my_subtitle_add_subtitle(MySubtitle *self,gchar *text,gdouble start,gdouble end,...);
void my_subtitle_del_subtitle(MySubtitle *self,guint64 index);
gchar* my_subtitle_to_string(MySubtitle *self);
gboolean my_subtitle_to_file(MySubtitle *self,gchar *location);
void my_subtitle_load_file(MySubtitle *self,gchar *location);
gchar *my_subtitle_get_subtitle(MySubtitle *self,guint64 index,gdouble *start,gdouble *end,...);
guint64 my_subtitle_get_total_size(MySubtitle *self);

void time_to_hh_mm_ss_sss(gdouble time,guint *hour,guint *minute,gdouble *second);
void remove_white_space(gchar *text);
G_END_DECLS

#endif /* SUBTITLE_SUBTITLE_H_ */
