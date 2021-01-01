/*
 * SubTitle.c
 *
 *  Created on: 2019年11月21日
 *      Author: tom
 */

#include "SubTitle.h"

G_DEFINE_BOXED_TYPE(MySubTitle, my_sub_title, my_sub_title_copy,
		my_sub_title_free)

MySubTitle *my_sub_title_copy(MySubTitle *self) {
	MySubTitle *cp = g_malloc0(sizeof(MySubTitle));
	cp->content = g_strdup(self->content);
	cp->end_ns = self->end_ns;
	cp->index = self->index;
	cp->show = self->show;
	cp->start_ns = self->start_ns;
	return cp;
}
;
void my_sub_title_free(MySubTitle *self) {
	g_free(self->content);
	g_free(self);
}
;

void my_sub_title_set_content(MySubTitle *self, gchar *content) {
	g_free(self->content);
	self->content = g_strdup(content);
}
;

