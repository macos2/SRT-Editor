/*
 * MainWin.c
 *
 *  Created on: 2019年11月21日
 *      Author: tom
 */

#include "MainWin.h"
#include "gresource.h"
typedef struct {
	GstElement *src, *video_convert, *audio_convert,*videosink,*audiosink;
	GstPipeline *pipeline;
	GHashTable *sub_title;
	GtkDrawingArea *content;
	GdkPixbuf *pixbuf;
} MyMainWinPrivate;

G_DEFINE_TYPE_WITH_CODE(MyMainWin, my_main_win, GTK_TYPE_WINDOW,
		G_ADD_PRIVATE(MyMainWin));

void my_main_win__new(GtkMenuItem *menuitem, MyMainWin *self) {
	g_print("New");
}
;

void my_main_win_open(GtkMenuItem *menuitem, MyMainWin *self) {
	gint repo;
	gchar *uri;
	MyMainWinPrivate *priv=my_main_win_get_instance_private(self);
	g_print("Open");
	GtkDialog *dialog=gtk_file_chooser_dialog_new("Open File",self,GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_OPEN,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
	repo=gtk_dialog_run(dialog);
	if(repo==GTK_RESPONSE_OK){
		uri=gtk_file_chooser_get_uri(dialog);
		if(uri!=NULL){
			g_object_set(priv->src, "uri", uri, NULL);
			g_free(uri);
			gst_element_set_state(priv->pipeline,GST_STATE_NULL);
			gst_element_set_state(priv->pipeline,GST_STATE_PLAYING);
		}
	}
	gtk_widget_destroy(dialog);

}
;

void my_main_win_save(GtkMenuItem *menuitem, MyMainWin *self) {
	g_print("Save");
}
;

void my_main_win_save_as(GtkMenuItem *menuitem, MyMainWin *self) {
	g_print("Save as");
}
;

gboolean content_draw_cb (GtkDrawingArea *content,
        cairo_t *cr,
		MyMainWin *self){
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gint w,h,cw,ch;
	gfloat radio;
	cairo_save(cr);
	cairo_set_source_rgba(cr,0.5,0,0,1.0);
	cairo_arc(cr,0,0,150,0,2*G_PI);
	cairo_set_line_width(cr,5);
	cairo_stroke(cr);
	cairo_restore(cr);
	if(priv->pixbuf!=NULL){
	cairo_save(cr);
	w=gdk_pixbuf_get_width(priv->pixbuf);
	h=gdk_pixbuf_get_height(priv->pixbuf);
	ch=gtk_widget_get_allocated_height(priv->content);
	cw=gtk_widget_get_allocated_width(priv->content);
	cairo_translate(cr,cw/2.,ch/2.);
	radio=(gfloat)cw/w;
	if(((gfloat)ch/h)<radio)radio=(gfloat)ch/h;
	cairo_scale(cr,radio,radio);
	gdk_cairo_set_source_pixbuf(cr,priv->pixbuf,-0.5*w,-0.5*h);
	cairo_paint(cr);
	cairo_restore(cr);
	}
	return TRUE;
}

void gst_bus_message_cb(GstBus *bus,GstMessage *message,MyMainWin *self){
	guint i;
	MyMainWinPrivate *priv=my_main_win_get_instance_private(self);
	GstStructure *s=gst_message_get_structure(message);
//	g_print("new %s:%s %d field msg\n",gst_message_type_get_name(message->type),gst_structure_get_name(s),gst_structure_n_fields(s));
	if(	gst_structure_has_field(s,"pixbuf")){
		if(priv->pixbuf!=NULL){
		gdk_pixbuf_unref(priv->pixbuf);
		}
		gst_structure_get(s,"pixbuf",GDK_TYPE_PIXBUF,&priv->pixbuf,NULL);
		gtk_widget_queue_draw(priv->content);
	}

//	for(i=0;i<gst_structure_n_fields(s);i++){
//		g_print("field:%s\n",gst_structure_nth_field_name(s,i));
//	}
}

void gst_src_new_pad(GstElement* object,GstPad* pad, MyMainWin *self){
	guint i,j;
	GstStructure *s;
	GstPad *sinkpad=NULL;
	MyMainWinPrivate *priv=my_main_win_get_instance_private(self);
	GstCaps *cap=gst_pad_get_current_caps(pad);
	i=gst_caps_get_size(cap);
	g_print("get new pad size:%d\n",i);
	for(j=0;j<i;j++){
	s=gst_caps_get_structure(cap,j);
	g_print("%2d:\"%s\"\n",j,gst_structure_get_name(s));

	if(g_strstr_len(gst_structure_get_name(s),-1,"video/x-raw")!=NULL){
		sinkpad=gst_element_get_static_pad(priv->video_convert,"sink");
		gst_pad_link(pad,sinkpad);
	};

	if(g_strstr_len(gst_structure_get_name(s),-1,"audio/x-raw")!=NULL){
		sinkpad=gst_element_get_static_pad(priv->audio_convert,"sink");
		gst_pad_link(pad,sinkpad);
	};
	}
	gst_caps_unref(cap);
	if(sinkpad!=NULL)gst_object_unref(sinkpad);
};


static void my_main_win_class_init(MyMainWinClass *klass) {
	gtk_widget_class_set_template_from_resource(klass, "/org/MainWin.glade");
	gtk_widget_class_bind_template_callback(klass, my_main_win__new);
	gtk_widget_class_bind_template_callback(klass, my_main_win_open);
	gtk_widget_class_bind_template_callback(klass, my_main_win_save);
	gtk_widget_class_bind_template_callback(klass, my_main_win_save_as);
	gtk_widget_class_bind_template_callback(klass, content_draw_cb);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin, content);
}
;

static void my_main_win_init(MyMainWin *self) {
	gtk_widget_init_template(self);
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	priv->sub_title = g_hash_table_new(g_direct_hash, g_direct_equal);
	priv->src = gst_element_factory_make("uridecodebin", "src");
	priv->video_convert = gst_element_factory_make("autovideoconvert", "video_convert");
	priv->audio_convert = gst_element_factory_make("audioconvert","audio_convert");
	priv->videosink = gst_element_factory_make("gdkpixbufsink", "gdkpixbufsink");
	priv->audiosink=gst_element_factory_make("autoaudiosink","audiosink");
	priv->pipeline = gst_pipeline_new("line");
	priv->pixbuf=NULL;
	gst_bin_add_many(priv->pipeline, priv->src, priv->audio_convert, priv->video_convert,priv->videosink,priv->audiosink,
	NULL);
	GstPad *sink=gst_element_get_static_pad(priv->videosink,"sink");
	GstPad *src=gst_element_get_static_pad(priv->video_convert,"src");
	gst_pad_link(src,sink);
	g_object_unref(sink);
	g_object_unref(src);

	sink=gst_element_get_static_pad(priv->audiosink,"sink");
	src=gst_element_get_static_pad(priv->audio_convert,"src");
	gst_pad_link(src,sink);
	g_object_unref(sink);
	g_object_unref(src);

	GstBus *bus=gst_pipeline_get_bus(priv->pipeline);
	g_signal_connect(bus,"message",gst_bus_message_cb,self);
	gst_bus_add_signal_watch (bus);
	g_signal_connect(priv->src,"pad-added",gst_src_new_pad,self);

}
;

MyMainWin *my_main_win_new(gchar *title, gchar *uri, gboolean play) {
	MyMainWin *m = g_object_new(MY_TYPE_MAIN_WIN, NULL);
	MyMainWinPrivate *priv = my_main_win_get_instance_private(m);
	GstStateChangeReturn state;
	if (title != NULL)
		gtk_window_set_title(m, title);
	if (uri != NULL)
		g_object_set(priv->src, "uri", uri, NULL);
	if (play){
		state=gst_element_set_state(priv->pipeline, GST_STATE_PLAYING);
		g_print("state:%02x\n",state);
	}
	return m;
}
;

