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
G_BEGIN_DECLS
#define MY_TYPE_SUBTITLE my_subtitle_get_type()
G_DECLARE_INTERFACE(MySubtitle,my_subtitle,MY,SUBTITLE,GObject);

typedef struct _MySubtitleInterface{
GTypeInterface parent_iface;
guint64 (*add_subtitle)(MySubTitle *self,gchar *text,gdouble start,gdouble end,va_list ap);
void (*del_subtitle)(MySubtitle *self,guint64 index);
gchar *(*to_string)(MySubtitle *self);
gboolean (*to_file)(MySubtitle *self,gchar *location);
void (*load_file)(MySubTitle *self,gchar *location);
gchar *(*get_subtitle)(MySubtitle *self,guint64 index);
guint64 (*get_total_size)(MySubtitle *self);
};

guint64 my_subtitle_add_subtitle(MySubTitle *self,gchar *text,gdouble start,gdouble end,...);
void my_subtitle_del_subtitle(MySubtitle *self,guint64 index);
gchar* my_subtitle_to_string(MySubtitle *self);
gboolean my_subtitle_to_file(MySubtitle *self,gchar *location);
void my_subtitle_load_file(MySubTitle *self,gchar *location);
void time_to_hh_mm_ss_sss(gdouble time,guint *hour,guint *minute,gdouble *second);
G_END_DECLS

#endif /* SUBTITLE_SUBTITLE_H_ */
