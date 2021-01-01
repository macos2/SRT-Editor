/*
 * SubTitleDisplay.h
 *
 *  Created on: 2019年11月28日
 *      Author: tom
 */

#ifndef UI_SUBTITLEDISPLAY_H_
#define UI_SUBTITLEDISPLAY_H_
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS
#define MY_TYPE_SUB_TITLE_DISPLAY my_sub_title_display_get_type()
G_DECLARE_DERIVABLE_TYPE(MySubTitleDisplay,my_sub_title_display,MY,SUB_TITLE_DISPLAY,GtkBox)

typedef struct _MySubTitleDisplayClass{
	GtkBoxClass parent_class;
};

MySubTitleDisplay *my_sub_title_display_new(gchar *subtitle,gdouble start_ns,gdouble end_ns);

G_END_DECLS


#endif /* UI_SUBTITLEDISPLAY_H_ */
