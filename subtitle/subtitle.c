/*
 * subtitle.c
 *
 *  Created on: 2021年1月8日
 *      Author: tom
 */

#include "subtitle.h"

G_DEFINE_INTERFACE(MySubtitle, my_subtitle, G_TYPE_OBJECT);

static void my_subtitle_default_init(MySubtitleInterface *iface) {

}

guint64 my_subtitle_add_subtitle(MySubTitle *self, gchar *text, gdouble start,
		gdouble end, ...) {
	MySubtitleInterface *iface = MY_SUBTITLE_GET_IFACE(self);
	va_list ap;
	guint64 res = 0;
	if (iface->add_subtitle != NULL) {
		va_start(ap, end);
		res = iface->add_subtitle(self, text, start, end, ap);
		va_end(ap);
	}
	return res;
}

void my_subtitle_del_subtitle(MySubtitle *self, guint64 index) {
	MySubtitleInterface *iface = MY_SUBTITLE_GET_IFACE(self);
	if(iface->del_subtitle!=NULL){
		iface->del_subtitle(self,index);
	}
}

gchar* my_subtitle_to_string(MySubtitle *self) {
	gchar *res=NULL;
	MySubtitleInterface *iface = MY_SUBTITLE_GET_IFACE(self);
	if(iface->to_string!=NULL){
		res=iface->to_string(self);
	}
	return res;
}

gboolean my_subtitle_to_file(MySubtitle *self, gchar *location) {
	gboolean res=FALSE;
	MySubtitleInterface *iface = MY_SUBTITLE_GET_IFACE(self);
	if(iface->to_file!=NULL){
		res=iface->to_file(self,location);
	}
	return res;
}

void my_subtitle_load_file(MySubTitle *self,gchar *location){
	MySubtitleInterface *iface = MY_SUBTITLE_GET_IFACE(self);
	if(iface->load_file!=NULL){
		iface->load_file(self,location);
	}
}

void time_to_hh_mm_ss_sss(gdouble time,guint *hour,guint *minute,gdouble *second){

}
