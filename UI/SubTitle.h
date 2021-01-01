/*
 * SubTitle.h
 *
 *  Created on: 2019年11月21日
 *      Author: tom
 */

#ifndef UI_SUBTITLE_H_
#define UI_SUBTITLE_H_

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS
//#define MY_TYPE_SUB_TITLE my_sub_title_get_type()
typedef struct{
	gboolean show;
	gchar *content;
	gdouble start_ns,end_ns;
	gdouble index;
}MySubTitle;

MySubTitle *my_sub_title_copy(MySubTitle *self);
void my_sub_title_free(MySubTitle *self);
void my_sub_title_set_content(MySubTitle *self,gchar *content);
G_END_DECLS

#endif /* UI_SUBTITLE_H_ */
