/*
 * subtitle.c
 *
 *  Created on: 2021年1月8日
 *      Author: tom
 */

#include "subtitle.h"

G_DEFINE_INTERFACE(MySubtitle, my_subtitle, G_TYPE_OBJECT);

static void my_subtitle_default_init(MySubtitleInterface *iface) {
iface->add_subtitle=NULL;
iface->del_subtitle=NULL;
iface->get_subtitle=NULL;
iface->get_total_size=NULL;
iface->load_file=NULL;
iface->to_file=NULL;
iface->to_string=NULL;
}

guint64 my_subtitle_add_subtitle(MySubtitle *self, gchar *text, gdouble start,
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

void my_subtitle_load_file(MySubtitle *self,gchar *location){
	MySubtitleInterface *iface = MY_SUBTITLE_GET_IFACE(self);
	if(iface->load_file!=NULL){
		iface->load_file(self,location);
	}
}

gchar *my_subtitle_get_subtitle(MySubtitle *self,guint64 index,gdouble *start,gdouble *end,...){
	gchar *subtitle=NULL;
	MySubtitleInterface *iface= MY_SUBTITLE_GET_IFACE(self);
	va_list ap;
	va_start(ap,end);
	if(iface->get_subtitle!=NULL){
		subtitle=iface->get_subtitle(self,index,start,end,ap);
	}
	va_end(ap);
	return subtitle;
}
guint64 my_subtitle_get_total_size(MySubtitle *self){
	guint64 size=0;
	MySubtitleInterface *iface= MY_SUBTITLE_GET_IFACE(self);
	if(iface->get_total_size!=NULL){
		size=iface->get_total_size(self);
	}
	return size;
}


void time_to_hh_mm_ss_sss(gdouble time,guint *hour,guint *minute,gdouble *second){
*hour=(guint)time/3600;
*minute=(guint)(time-*hour*3600)/60;
*second=(time-*hour*3600.-*minute/60.);
}

void remove_white_space(gchar *text){
	gchar *p,*w;
	p=text;
	w=text;
	while(*p!='\0'){
		if(*p!=' '){
			*w=*p;
			w++;
		}
		p++;
	}
	*w='\0';
}
