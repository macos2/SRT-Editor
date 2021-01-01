/*
 * SubTitleDisplay.c
 *
 *  Created on: 2019年11月28日
 *      Author: tom
 */


#include "SubTitleDisplay.h"
#include "gresource.h"
typedef struct {
	gchar *subtitle;
	gdouble start_ns,end_ns;

}MySubTitleDisplayPrivate;

G_DEFINE_TYPE_WITH_CODE(MySubTitleDisplay,my_sub_title_display,GTK_TYPE_BOX,G_ADD_PRIVATE(MySubTitleDisplay));

void my_sub_title_display_finalize(MySubTitleDisplay *self){
	MySubTitleDisplayPrivate *priv=my_sub_title_display_get_instance_private(self);
	g_free(priv->subtitle);
}

static void my_sub_title_display_class_init(MySubTitleDisplayClass *klass){
	GObjectClass *gclass=klass;
	gclass->finalize=my_sub_title_display_finalize;
	gtk_widget_class_set_template_from_resource(klass,"/org/SubTitleDisplay.glade");

}

static void my_sub_title_display_init(MySubTitleDisplay *self){
	gtk_widget_init_template(self);

}

MySubTitleDisplay *my_sub_title_display_new(gchar *subtitle,gdouble start_ns,gdouble end_ns){
	MySubTitleDisplay *n=g_object_new(MY_TYPE_SUB_TITLE_DISPLAY,NULL);
	MySubTitleDisplayPrivate *priv=my_sub_title_display_get_instance_private(n);
	priv->end_ns=end_ns;
	priv->start_ns=start_ns;
	priv->subtitle=g_strdup(subtitle);
	return n;
};
