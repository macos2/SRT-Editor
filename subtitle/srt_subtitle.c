/*
 * srt_subtitle.c
 *
 *  Created on: 2021年1月8日
 *      Author: tom
 */



#include "srt_subtitle.h"

typedef struct {
	GdkRGBA color;
	gchar *font;
	gchar *subtitle;
	gdouble start,end;
}SRTSubtitleData;

typedef struct{
	GTree *tree;
	guint64 index;
}MySrtSubtitlePrivate;

G_DEFINE_TYPE_WITH_CODE(MySrtSubtitle,my_srt_subtitle,G_TYPE_OBJECT,G_ADD_PRIVATE(MySrtSubtitle)\
																	G_IMPLEMENT_INTERFACE(MY_TYPE_SUBTITLE,my_srt_subtitle_subtitle_iface_init))

SRTSubtitleData * srt_subtitle_data_new(gchar *subtitle,gchar *font,GdkRGBA *color,gdouble start,gdouble end){
	SRTSubtitleData *data=g_malloc(sizeof(SRTSubtitleData));
	data->font=g_strdup(font);
	data->subtitle=g_strdup(subtitle);
	data->start=start;
	data->end=end;
	if(color!=NULL){
	data->color.alpha=color->alpha;
	data->color.blue=color->blue;
	data->color.green=color->green;
	data->color.red=color->red;
	}
	return data;
}

gint srt_subtitle_data_compare (SRTSubtitleData * a,SRTSubtitleData *  b, gpointer  user_data){
	if(a->start>b->start)return -1;
	return 1;
}

void srt_subtitle_data_free(SRTSubtitleData *data){
	g_free(data->font);
	g_free(data->subtitle);
	g_free(data);
}

void       my_srt_subtitle_dispose			(MySrtSubtitle *self){

};

void       my_srt_subtitle_finalize		(MySrtSubtitle *self){
	MySrtSubtitlePrivate *priv=my_srt_subtitle_get_instance_private(self);
	g_tree_destroy(priv->tree);
};


static void my_srt_subtitle_subtitle_iface_init(MySubtitleInterface *iface){
iface->add_subtitle=my_srt_subtitle_add_subtitle;
iface->del_subtitle=my_srt_subtitle_del_subtitle;
//iface->parent_iface=NULL;
iface->to_file=my_srt_subtitle_to_file;
iface->to_string=my_srt_subtitle_to_string;
iface->load_file=my_srt_subtitle_load_file;
}

static void my_srt_subtitle_class_init(MySrtSubtitleClass *klass){
GObjectClass *obj_class=klass;
obj_class->finalize=my_srt_subtitle_finalize;
}

static void my_srt_subtitle_init(MySrtSubtitle *self){
MySrtSubtitlePrivate *priv=my_srt_subtitle_get_instance_private(self);
priv->tree=g_tree_new_full(srt_subtitle_data_compare,NULL,NULL,srt_subtitle_data_free);
priv->index=0;
}

guint64 my_srt_subtitle_add_subtitle(MySrtSubtitle *self,gchar *text,gdouble start,gdouble end,va_list ap){
	GdkRGBA *color=NULL;
	gchar *font=NULL;
	gint format;
	MySrtSubtitlePrivate *priv=my_srt_subtitle_get_instance_private(self);
	do{
	format=va_arg(ap,gint);
	if(format==-1||format==0)break;
	if(format==Srt_Color)color=va_arg(ap,GdkRGBA *);
	if(format==Srt_Font)font=va_arg(ap,gchar *);
	}while(1);
	SRTSubtitleData *data=srt_subtitle_data_new(text,font,color,start,end);
	g_tree_insert(priv->tree,GINT_TO_POINTER(priv->index),data);
	priv->index++;
	return priv->index-1;
}

void my_srt_subtitle_del_subtitle(MySrtSubtitle*self,guint64 index){
	MySrtSubtitlePrivate *priv=my_srt_subtitle_get_instance_private(self);
	g_tree_remove(priv->tree,GINT_TO_POINTER(index));
}


void my_srt_subtitle_to_file(MySrtSubtitle*self,gchar *location){

}

gchar *my_srt_subtitle_to_string(MySrtSubtitle *self){

}

void my_srt_subtitle_load_file(MySrtSubtitle *self,gchar *location){

}

