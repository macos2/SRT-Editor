/*
 * MyVideoAlbum.c
 *
 *  Created on: 2021年1月31日
 *      Author: tom
 */

#include "MyVideoAlbum.h"
#include "string_helper.h"
#include "../ui/gresource.h"

guint __album_index;//the order of the album ,start from 0 to __video_num
guint __video_num;//the num of video to generate album
guint __finish_album;//the num of album which have been generate.

typedef struct{
	guint width,mini_count,max_count;
	gchar *save_dir,*file_format;
}ThreadSetting;

typedef struct {
	GtkCheckButton *with_video_dir;
	GtkEntry *file_name_format;
	GtkFileChooserButton *save_dir, *video_dir;
	GAsyncQueue *queue;
	GThreadPool *pool;
	GtkSpinButton *width,*mini_count,*max_count;
	ThreadSetting *setting;
	GtkLevelBar *progress;
	GtkButton *generate_album;
	GtkFileFilter *video_filter;
} MyVideoAlbumPrivate;

G_DEFINE_TYPE_WITH_CODE(MyVideoAlbum, my_video_album, GTK_TYPE_WINDOW,
		G_ADD_PRIVATE(MyVideoAlbum))

void query_all_the_file (MyVideoAlbum *self,gchar *dir_path) {
	MyVideoAlbumPrivate *priv = my_video_album_get_instance_private(self);
	gchar *temp,*path;
	GDir *dir=g_dir_open(dir_path,0,NULL);
	while(1){
	temp=g_dir_read_name(dir);
	if(temp==NULL)break;
	path=g_strdup_printf("%s%c%s",dir_path,G_DIR_SEPARATOR,temp);
	if(g_file_test(path,G_FILE_TEST_IS_DIR)) {
		query_all_the_file(self,path);
	} else if(g_file_test(path,G_FILE_TEST_IS_REGULAR)) {
		g_async_queue_push(priv->queue,g_strdup(path));
	}
	g_free(path);
	}
	g_dir_close(dir);
}

gchar *general_album_filepath(gchar *file_path,gchar *format,gchar *save_dir,gint w,gint h,gdouble duration){
	gchar *new_name=g_strdup(format),*temp;
	GFile *d;
	GFile *f=g_file_new_for_path(file_path);
	if(save_dir==NULL)
		d=g_file_get_parent(f);
	else
		d=g_file_new_for_path(save_dir);
	gchar *filename=g_file_get_basename(f);
	gchar *dir=g_file_get_basename(d);
	gchar *dir_path=g_file_get_path(d);
	if(new_name==NULL){
		new_name=g_strdup_printf("%s%c%s.png",dir_path,G_DIR_SEPARATOR,filename);
		goto end;
	}
	guint i=__album_index;
	guint hour=(guint)duration/3600;
	guint minute=((guint)duration-hour*3600)/60;
	gdouble second=duration-hour*3600-minute*60;
	if(g_strstr_len(new_name,-1,"%i")){
		temp=g_strdup_printf("%04d",i);
		string_replace(&new_name,"%i",temp);
		g_free(temp);
	}
	if(g_strstr_len(new_name,-1,"%hour")){
		temp=g_strdup_printf("%02d",hour);
		string_replace(&new_name,"%hour",temp);
		g_free(temp);
	}
	if(g_strstr_len(new_name,-1,"%min")){
		temp=g_strdup_printf("%02d",minute);
		string_replace(&new_name,"%min",temp);
		g_free(temp);
	}
	if(g_strstr_len(new_name,-1,"%sec")){
		temp=g_strdup_printf("%6.3lf",second);
		string_replace(&new_name,"%sec",temp);
		g_free(temp);
	}
	if(g_strstr_len(new_name,-1,"%dir")){
		string_replace(&new_name,"%dir",dir);
	}
	if(g_strstr_len(new_name,-1,"%d")){
		temp=g_strdup_printf("%.3lf",duration);
		string_replace(&new_name,"%d",temp);
		g_free(temp);
	}
	if(g_strstr_len(new_name,-1,"%w")){
		temp=g_strdup_printf("%d",w);
		string_replace(&new_name,"%w",temp);
		g_free(temp);
	}
	if(g_strstr_len(new_name,-1,"%h")){
		temp=g_strdup_printf("%d",h);
		string_replace(&new_name,"%h",temp);
		g_free(temp);
	}
	if(g_strstr_len(new_name,-1,"%f")){
		string_replace(&new_name,"%f",filename);
	}
	temp=g_strdup_printf("%s%c%s",dir_path,G_DIR_SEPARATOR,new_name);
	g_free(new_name);
	new_name=temp;
	end:
	__album_index++;
	g_object_unref(d);
	g_object_unref(f);
	g_free(filename);
	g_free(dir);
	g_free(dir_path);
	return new_name;
}

GstPipeline *general_pipeline(gchar *file_path){
	GstPipeline *line=gst_pipeline_new(NULL);
	GstElement *src,*sink,*nullsink;
	src=gst_element_factory_make("playbin","src");
	sink=gst_element_factory_make("gdkpixbufsink","sink");
	nullsink=gst_element_factory_make("fakesink","null");
	gst_bin_add_many(line,src,NULL);
#ifdef G_OS_WIN32
	gchar *t=g_strdup(file_path);
	string_replace(&t,"\\","/");
	gchar *temp=g_strdup_printf("file:///%s",t);
	g_free(t);
#else
	gchar *temp=g_strdup_printf("file://%s",file_path);
#endif
	g_object_set(src,"video-sink",sink,"audio-sink",nullsink,"uri",temp,NULL);
	g_free(temp);
	return line;
}


void general_album_thread(gchar *file,ThreadSetting *setting){
	if(file==NULL)return;
	g_print("%s(%s)\n",__func__,file);
	gboolean te;
	gboolean exit=FALSE;
	gchar *debug;
	GError *err;
	GstStructure *s;
	GdkPixbuf *pixbuf=NULL;
	guint64 duration;
	guint count=setting->mini_count,i=0;
	guint64 interval=0,cur;
	guint hour,minute;
	gdouble second;
	gchar *temp=NULL;
	gst_init(NULL,NULL);
	GstPipeline *line=general_pipeline(file);
	g_free(temp);
	gchar *display_name;
	GstMessage *msg=NULL;
	gint w,h,surf_w,surf_h,row=0,col=0;
	gdouble radio=1.;
	cairo_surface_t *surf=NULL;
	cairo_t *cr=NULL;
	cairo_text_extents_t text_ex;
	GstBus *bus=gst_pipeline_get_bus(line);
	gst_element_set_state(line,GST_STATE_PLAYING);
	while(1){
		//msg=gst_bus_pop_filtered(bus,GST_MESSAGE_ELEMENT|GST_MESSAGE_EOS|GST_MESSAGE_ERROR);
		msg=gst_bus_timed_pop_filtered(bus,20*GST_SECOND,GST_MESSAGE_ELEMENT|GST_MESSAGE_EOS|GST_MESSAGE_ERROR);
		if(msg==NULL)break;
		switch(msg->type){
		case GST_MESSAGE_ELEMENT:
			gst_bus_set_flushing (bus,TRUE);
			s=gst_message_get_structure(msg);
			gst_structure_get(s,"pixbuf",GDK_TYPE_PIXBUF,&pixbuf,NULL);
			if(pixbuf!=NULL){
				if(surf==NULL){//the surface have not been init.
					gst_element_query_duration(line,GST_FORMAT_TIME,&duration);
					if(duration==G_MAXUINT64){//it is a image not a video
						exit=TRUE;
						break;
					}
					if(duration>(setting->mini_count*30000000000)){
						count=duration/30000000000;
						if(count>setting->max_count)count=setting->max_count;
					}
					interval=duration/count;
					w=gdk_pixbuf_get_width(pixbuf);
					h=gdk_pixbuf_get_height(pixbuf);
					radio=256./w;
					surf_w=(256+20)*6;
					surf_h=ceil(count/6.)*(h*radio+20)+87;
					surf=cairo_image_surface_create(CAIRO_FORMAT_RGB24,surf_w,surf_h);
					cr=cairo_create(surf);
					cairo_set_source_rgb(cr,0,0,0);
					cairo_rectangle(cr,0,0,surf_w,surf_h);
					cairo_fill(cr);
#ifdef G_OS_WIN32
					cairo_select_font_face(cr,"sans-serif",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
#endif
					cairo_set_source_rgb(cr,1.,1.,1.);
					cairo_set_font_size(cr,24.);
					display_name=g_filename_display_basename(file);
					temp=g_strdup_printf("File       : %s",display_name);
					cairo_text_extents(cr,temp,&text_ex);
					cairo_move_to(cr,5,5+text_ex.height);
					cairo_show_text(cr,temp);
					cairo_fill(cr);
					g_free(temp);
					g_free(display_name);
					temp=g_strdup_printf("Resolution : %d x %d",w,h);
					cairo_text_extents(cr,temp,&text_ex);
					cairo_move_to(cr,5,34+text_ex.height);
					cairo_show_text(cr,temp);
					cairo_fill(cr);
					g_free(temp);
					time_to_hh_mm_ss_sss(duration/1000000000.,&hour,&minute,&second);
					temp=g_strdup_printf("Duration   : %02u : %02u : %04.1lf <--> %4.1f s",hour,minute,second,duration/1000000000.);
					cairo_text_extents(cr,temp,&text_ex);
					cairo_move_to(cr,5,63+text_ex.height);
					cairo_show_text(cr,temp);
					cairo_fill(cr);
					g_free(temp);
				}
				//show the image of the frame.
				cairo_save(cr);
				cairo_translate(cr,col*(256+20)+10,row*(h*radio+20)+10.+87.);
				cairo_scale(cr,radio,radio);
				gdk_cairo_set_source_pixbuf(cr,pixbuf,0,0);
				col++;
				if(col>=6){
					row++;
					col=0;
				}
				cairo_paint(cr);
				gdk_pixbuf_unref(pixbuf);
				pixbuf=NULL;
				//show the time of the frame
				cairo_scale(cr,1./radio,1./radio);
				//cairo_translate(cr,col*(256+20)+10,row*(h*radio+20)+10.+87.);
				cairo_set_source_rgb(cr,1.,1.,1.);
				cairo_set_font_size(cr,16.);

				time_to_hh_mm_ss_sss((i*interval)/1000000000.,&hour,&minute,&second);
				temp=g_strdup_printf("%02u : %02u : %04.1lf",hour,minute,second);
				cairo_text_extents(cr,temp,&text_ex);
				cairo_move_to(cr,2,text_ex.height+2.);
				cairo_show_text(cr,temp);
				cairo_fill(cr);
				g_free(temp);
				cairo_restore(cr);
				cairo_surface_flush(surf);
			}
			if(i<count){
				i++;
				te=gst_element_seek_simple(line,GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE,i*interval);
				gst_element_set_state(line,GST_STATE_PAUSED);
				gst_element_set_state (line,GST_STATE_PLAYING);
				//gst_bus_set_flushing (bus,FALSE);
			}else{
				exit=TRUE;
			}
			break;
		case GST_MESSAGE_ERROR:
			gst_message_parse_error(msg,&err,&debug);
			g_printerr("File:\t%s\nError:\t%s\nDebug:\t%s\n\n",file,err->message,debug);
			g_free(debug);
			g_error_free(err);
		case GST_MESSAGE_EOS:
		default:
			exit=TRUE;
			break;
		}
		  if (msg != NULL){
		    gst_message_unref (msg);
		    msg=NULL;
		  }
		if(exit)break;
	}
	gst_object_unref(bus);
	gst_element_set_state(line,GST_STATE_NULL);
	gst_object_unref(line);
	if(surf!=NULL){
	gchar *file_path=general_album_filepath(file,setting->file_format,setting->save_dir,w,h,duration/1000000000.);
	if(g_strcmp0(file_path,file)==0){//if the file_path is same with the video file,add a suffix ".png" to avoid overwrite the video file.
		temp=g_strdup_printf("%s.png",file_path);
		g_free(file_path);
		file_path=temp;
	}
	cairo_surface_write_to_png(surf,file_path);
	g_free(file_path);
	cairo_destroy(cr);
	cairo_surface_destroy(surf);
	}
	g_free(file);
	fflush(NULL);
	__finish_album++;

}

gboolean my_video_album_watch ( MyVideoAlbum *self){
	MyVideoAlbumPrivate *priv = my_video_album_get_instance_private(self);
	gtk_level_bar_set_value(priv->progress,__finish_album);
	if(g_thread_pool_get_num_threads(priv->pool)==0){
		gtk_widget_set_sensitive(priv->generate_album,TRUE);
		return G_SOURCE_REMOVE;
	}
	return G_SOURCE_CONTINUE;
}

void general_album_cb(GtkButton *button, MyVideoAlbum *self) {
	gchar *file_path;
	gchar *filename,*suffix,*p;
	__album_index=0;
	__finish_album=0;
	MyVideoAlbumPrivate *priv = my_video_album_get_instance_private(self);
	gchar *temp = gtk_file_chooser_get_filename(priv->video_dir);
	if(temp==NULL)return;
	query_all_the_file(self,temp);
	ThreadSetting *setting=priv->setting;
	setting->file_format=gtk_entry_get_text(priv->file_name_format);
	setting->mini_count=gtk_spin_button_get_value_as_int(priv->mini_count);
	setting->max_count=gtk_spin_button_get_value_as_int(priv->max_count);
	setting->save_dir=NULL;
	if(!gtk_toggle_button_get_active(priv->with_video_dir))
		setting->save_dir=gtk_file_chooser_get_filename(priv->save_dir);
	setting->width=gtk_spin_button_get_value_as_int(priv->width);
	__video_num=g_async_queue_length(priv->queue);
	while(g_async_queue_length(priv->queue)>0){
		file_path=g_async_queue_pop(priv->queue);
		filename=g_filename_display_basename(file_path);
		suffix=g_ascii_strdown(filename,-1);
		g_free(filename);
		filename=suffix;
		while(1){
			p=g_strstr_len(suffix+1,-1,".");
			if(p==NULL)break;
			suffix=p;
		}
		if(g_strstr_len(suffix,-1,".png")||g_strstr_len(suffix,-1,".jpg")||g_strstr_len(suffix,-1,".jpeg")){
			g_free(file_path);
			file_path=NULL;
			__video_num--;
		}
		g_free(filename);
		if(file_path!=NULL)g_thread_pool_push(priv->pool,file_path,NULL);
	}
	gtk_level_bar_set_max_value(priv->progress,__video_num);
	g_timeout_add(250,my_video_album_watch,self);
	gtk_widget_set_sensitive(priv->generate_album,FALSE);
	g_free(temp);
}

void with_video_dir_toggled_cb(GtkCheckButton *button, MyVideoAlbum *self){
	gboolean active;
	MyVideoAlbumPrivate *priv = my_video_album_get_instance_private(self);
	active=gtk_toggle_button_get_active(button);
	active=active?FALSE:TRUE;
	gtk_widget_set_sensitive(priv->save_dir,active);
}

static void my_video_album_class_init(MyVideoAlbumClass *klass) {
	gtk_widget_class_set_template_from_resource(klass, "/org/VideoAlbum.glade");
	gtk_widget_class_bind_template_child_private(klass, MyVideoAlbum,
			with_video_dir);
	gtk_widget_class_bind_template_child_private(klass, MyVideoAlbum,
			file_name_format);
	gtk_widget_class_bind_template_child_private(klass, MyVideoAlbum, save_dir);
	gtk_widget_class_bind_template_child_private(klass, MyVideoAlbum,
			video_dir);
	gtk_widget_class_bind_template_child_private(klass, MyVideoAlbum,
			width);
	gtk_widget_class_bind_template_child_private(klass, MyVideoAlbum,
			mini_count);
	gtk_widget_class_bind_template_child_private(klass, MyVideoAlbum,
			progress);
	gtk_widget_class_bind_template_child_private(klass, MyVideoAlbum,
			generate_album);
	gtk_widget_class_bind_template_child_private(klass, MyVideoAlbum,
			max_count);
	gtk_widget_class_bind_template_child_private(klass, MyVideoAlbum,
			video_filter);
	gtk_widget_class_bind_template_callback(klass,general_album_cb);
	gtk_widget_class_bind_template_callback(klass,with_video_dir_toggled_cb);
}

static void my_video_album_init(MyVideoAlbum *self) {
	gtk_widget_init_template(self);
	gchar *photo_dir=g_get_user_special_dir(G_USER_DIRECTORY_PICTURES);
	MyVideoAlbumPrivate *priv = my_video_album_get_instance_private(self);
	priv->queue=g_async_queue_new();
	priv->setting=malloc(sizeof(ThreadSetting));
	priv->pool=g_thread_pool_new(general_album_thread,priv->setting,1,FALSE,NULL);

	if(photo_dir!=NULL)gtk_file_chooser_set_current_folder(priv->save_dir,photo_dir);
}

MyVideoAlbum* my_video_album_new(){
	return g_object_new(MY_TYPE_VIDEO_ALBUM,NULL);
};
