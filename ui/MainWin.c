/*
 * MainWin.c
 *
 *  Created on: 2019年11月21日
 *      Author: tom
 */

#include "../ui/MainWin.h"
#include "string_helper.h"
#include "../ui/gresource.h"
#define SUBTITLE_LIST_TIME_FORMAT "%.3f s"

typedef struct {
	GstElement *src, *video_convert, *audio_convert, *videosink, *audiosink,
			*volume;
	GstPipeline *pipeline;
	GHashTable *subtitle_table;
	GtkDrawingArea *content;
	GdkPixbuf *pixbuf;
	GtkScale *video_progress;
	GstState cur_state;
	GtkScrolledWindow *subtitle_trace;
	MyTraceBar *trace_bar;
	GtkInfoBar *info_bar;
	GtkLabel *info_message;
	guint info_timeout;
	GtkToggleButton *mul_photo;
	GtkCheckButton *photo_save_as_video_dir, *auto_pause;
	GtkFileChooserButton *photo_save_as_special_dir;
	GtkSpinButton *default_subtitle_last_time, *subtitle_last_time;
	GtkEntry *subtitle;
	GtkPopoverMenu *pop_menu;
	GtkSpinButton *pop_menu_start, *pop_menu_end;
	GtkEntry *pop_menu_subtitle, *pop_menu_label, *subtitle_list_edit_pattern,
			*subtitle_list_edit_format,*find_entry;
	GtkColorButton *subtitle_color, *subtitle_font_fill_color,
			*subtitle_font_stroke_color, *pop_menu_color;
	guint64 subtitle_index;
	GList *active_subtitle;
	GtkFontButton *subtitle_font;
	gpointer *selected_index;
	GtkPopover *pop_label, *ex_popover, *pop_subtitle_list;
	GtkLabel *pop_label_text;
	GtkButton *pop_menu_ex_menu, *ex_menu, *subtitle_list_edit;
	GtkStack *char_stack;
	GRegex *markup;
	GtkListStore *subtitle_list, *subtitle_list_edit_preview;
	GtkTreeView *subtitle_treeview;
	GtkDrawingArea *pop_label_preview;
	GThreadPool *take_photo_thread;
	GtkDialog *subtitle_list_edit_dialog;
	MyVideoAlbum *videoalbum;
} MyMainWinPrivate;

enum {
	col_index,
	col_start,
	col_start_text,
	col_end,
	col_end_text,
	col_text,
	col_preview,
	col_active,
} SubtitleListCol;

enum {
	col_edit_preview_index, col_edit_preview_beforce, col_edit_preview_after,
} SubtitleListEditPreviewCol;

typedef struct {
	guint64 index;
	GtkTreeRowReference *ref;
	gchar *subtitle;
} SubtitleDictData;

G_DEFINE_TYPE_WITH_CODE(MyMainWin, my_main_win, GTK_TYPE_WINDOW,
		G_ADD_PRIVATE(MyMainWin));

gboolean my_main_win_tree_row_ref_get_iter(GtkTreeRowReference *ref,
		GtkTreeIter *iter) {
	GtkTreePath *path = gtk_tree_row_reference_get_path(ref);
	GtkTreeModel *model = gtk_tree_row_reference_get_model(ref);
	gboolean res = gtk_tree_model_get_iter(model, iter, path);
	gtk_tree_path_free(path);
	return res;
}

gboolean content_button_press_event_cb(GtkDrawingArea *area,
		GdkEventButton *event, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gtk_popover_popdown(priv->ex_popover);
	gtk_popover_popdown(priv->pop_label);
	gtk_popover_popdown(priv->pop_menu);
	gtk_popover_popdown(priv->pop_subtitle_list);
	return TRUE;
}

void my_main_win__new(GtkMenuItem *menuitem, MyMainWin *self) {
	g_print("New");
}
;

void my_main_win_open(GtkMenuItem *menuitem, MyMainWin *self) {
	gint repo;
	gchar *uri;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	g_object_get(priv->src, "uri", &uri, NULL);
	GtkDialog *dialog = gtk_file_chooser_dialog_new("Open File", self,
			GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OPEN, GTK_RESPONSE_OK,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	gtk_file_chooser_set_uri(dialog, uri);
	g_free(uri);
	repo = gtk_dialog_run(dialog);
	if (repo == GTK_RESPONSE_OK) {
		uri = gtk_file_chooser_get_uri(dialog);
		if (uri != NULL) {
			gst_element_set_state(priv->pipeline, GST_STATE_NULL);
			gst_element_unlink(priv->src, priv->video_convert);
			gst_element_unlink(priv->src, priv->audio_convert);
//			gst_object_ref (priv->audio_convert);
//			gst_object_ref(priv->audiosink);
//			gst_object_ref(priv->volume);
//			gst_object_ref(priv->video_convert);
//			gst_object_ref(priv->videosink);
//			gst_bin_remove_many(priv->pipeline,priv->audio_convert,priv->audiosink,priv->video_convert,priv->videosink,priv->volume,NULL);
			g_object_set(priv->src, "uri", uri, NULL);
			g_free(uri);
			gst_element_set_state(priv->pipeline, priv->cur_state);
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
void my_main_win_video_dir_album(GtkMenuItem *menuitem, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gtk_widget_show_all(priv->videoalbum);
	gtk_widget_show_now(priv->videoalbum);
}

void my_main_win_prev_cb(GtkButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gst_element_set_state(priv->pipeline, GST_STATE_NULL);
	gst_element_set_state(priv->pipeline, GST_STATE_PAUSED);
	gst_element_set_state(priv->pipeline, priv->cur_state);
}

void my_main_win_play_cb(GtkButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gst_element_set_state(priv->pipeline, GST_STATE_PLAYING);
	priv->cur_state = GST_STATE_PLAYING;
}

void my_main_win_pause_cb(GtkButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gst_element_set_state(priv->pipeline, GST_STATE_PAUSED);
	priv->cur_state = GST_STATE_PAUSED;
}

void my_main_win_next_cb(GtkButton *button, MyMainWin *self) {
	gint64 dur;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GstQuery *duration = gst_query_new_duration(GST_FORMAT_TIME);
	GstBus *bus = gst_pipeline_get_bus(priv->pipeline);
	if (gst_element_query(priv->pipeline, duration)) {
		gst_query_parse_duration(duration, NULL, &dur);
	}
	gst_element_set_state(priv->pipeline, GST_STATE_PLAYING);
	gst_element_seek_simple(priv->pipeline, GST_FORMAT_TIME,
			GST_SEEK_FLAG_TRICKMODE | GST_SEEK_FLAG_SNAP_AFTER,
			dur - 5000000000);
	gst_element_set_state(priv->pipeline, priv->cur_state);
	gst_query_unref(duration);
	g_object_unref(bus);
}

gboolean video_progress_change_value_cb(GtkScrollbar *video_progress,
		GtkScrollType scroll, gdouble value, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gst_element_set_state(priv->pipeline, GST_STATE_PLAYING);
	gst_element_seek_simple(priv->pipeline, GST_FORMAT_TIME,
			GST_SEEK_FLAG_TRICKMODE | GST_SEEK_FLAG_SNAP_AFTER,
			value * 1000000);
	gst_element_set_state(priv->pipeline, priv->cur_state);
	return TRUE;
}

void volume_changed_cb(GtkScaleButton *button, gdouble value, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	g_object_set(priv->src, "volume", value / 100., NULL);
}

gchar* my_main_win_photo_name_generate(MyMainWin *self, gint64 time) {
	gchar *temp = NULL, *basename;
	gint64 pos;
	GFile *file, *dir;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	pos = time;
	if (time
			< 0&&gst_element_query_position(priv->pipeline,GST_FORMAT_TIME,&pos)==FALSE)
		pos = -1;

	g_object_get(priv->src, "current-uri", &temp, NULL);
	if (temp == NULL)
		return NULL;
	file = g_file_new_for_uri(temp);
	g_free(temp);
	basename = g_file_get_basename(file);

	if (gtk_toggle_button_get_active(priv->photo_save_as_video_dir)) {
		//save under the directory which is same as the video file.
		dir = g_file_get_parent(file);
	} else {
		//save under the directory which is user special.
		temp = gtk_file_chooser_get_uri(priv->photo_save_as_special_dir);
		dir = g_file_new_for_uri(temp);
		g_free(temp);
	}
	//if directory is could not be writed.
	if (g_access(g_file_peek_path(dir), W_OK) == -1) {
		g_object_unref(dir);
		temp = g_strdup_printf("%s%cSRT-Editor-Photo",
				g_get_user_special_dir(G_USER_DIRECTORY_PICTURES),
				G_DIR_SEPARATOR);
		dir = g_file_new_for_path(temp);
		g_free(temp);
	};
	//creat the directory if not exist.
	if (g_access(g_file_peek_path(dir), W_OK) == -1)
		g_mkdir_with_parents(g_file_peek_path(dir), 0775);

	if (pos >= 0) {
		//the time position is vaild
		temp = g_strdup_printf("%s%c%s@%.3f.png\0", g_file_peek_path(dir),
		G_DIR_SEPARATOR, basename, pos / 1000000000.);
	} else {
		//the time position is invaild
		pos = 0;
		temp = NULL;
		do {
			g_free(temp);
			temp = g_strdup_printf("%s%c%-%ld.png\0", g_file_peek_path(dir),
			G_DIR_SEPARATOR, basename, pos);
			pos++;
		} while (!g_access(temp, F_OK));
	}
	g_free(basename);
	g_object_unref(file);
	g_object_unref(dir);
	return temp;
}

void my_main_win_take_photo_cb(GtkButton *button, MyMainWin *self) {
	cairo_surface_t *surf;
	cairo_t *cr;
	gchar *temp;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	if (priv->pixbuf != NULL) {
		temp = my_main_win_photo_name_generate(self, -1);
		//if the file exist,remove it
		if (!g_access(temp, F_OK))
			g_remove(temp);
		surf = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
				gdk_pixbuf_get_width(priv->pixbuf),
				gdk_pixbuf_get_height(priv->pixbuf));
		cr = cairo_create(surf);
		gdk_cairo_set_source_pixbuf(cr, priv->pixbuf, 0, 0);
		cairo_paint(cr);
		if (cairo_surface_write_to_png(surf, temp) == CAIRO_STATUS_SUCCESS)
			my_main_win_info_bar_show_info(self, 2, "Photo is Saved as %s",
					temp);
		else
			my_main_win_info_bar_show_info(self, 2,
					"Photo is Failed to Saved as %s", temp);
		cairo_destroy(cr);
		cairo_surface_destroy(surf);
		g_free(temp);
	}
}

void my_main_win_take_photo_thread(gpointer *data, gpointer user_data) {
	GdkPixbuf *pixbuf = data[0];
	gchar *file_name = data[1];
	guint timeout = 0;
	cairo_status_t status;
	gint w = GPOINTER_TO_INT(data[2]);
	gint h = GPOINTER_TO_INT(data[3]);
	cairo_surface_t *surf = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w,
			h);
	cairo_t *cr = cairo_create(surf);
	gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
	cairo_paint(cr);
	do {
		timeout++;
		g_unlink(file_name);
		status = cairo_surface_write_to_png(surf, file_name);
	} while (status != CAIRO_STATUS_SUCCESS && timeout < 16);
	cairo_destroy(cr);
	cairo_surface_destroy(surf);
	g_object_unref(pixbuf);
	g_free(file_name);
	g_free(data);
}

GdkPixbuf* my_main_win_gen_subtitle_preview(MyMainWin *self, gchar *subtitle) {
	if (subtitle == NULL)
		return NULL;
	guint rows = 0;
	GdkRGBA font_color, stroke_color;
	gint h = 0, w = 0, layout_w, layout_h, t, max_width = 0, total_heigh = 0;
	gchar *p, *s, *temp;
	GdkPixbuf *result;
	PangoLayout *layout;
	cairo_t *cr;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	//compute how many rows of the subtitle
	temp = subtitle;
	p = subtitle;
	do {
		rows++;
		temp = g_strstr_len(temp, -1, "</br>");
		if (temp == NULL)
			break;
		t = g_utf8_strlen(p, temp - p);
		w = w > t ? w : t;
		p = temp + 5;
		temp++;
	} while (1);
	t = g_utf8_strlen(p, -1);
	w = w > t ? w : t;
	w = w * 25;
	h = rows * 25;

	//prepare the preview of the subtitle.
	cairo_surface_t *surf = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w,
			h);
	cr = cairo_create(surf);
	gtk_color_chooser_get_rgba(priv->subtitle_font_fill_color, &font_color);
	gtk_color_chooser_get_rgba(priv->subtitle_font_stroke_color, &stroke_color);
	s = subtitle;
	p = g_strstr_len(s, -1, "</br>");
	cairo_set_line_width(cr, 0.5);
	while (p != NULL) {
		temp = g_strndup(s, p - s);
		layout = my_subtitle_parse_srt_text_line(cr, &font_color,
				gtk_font_chooser_get_font_family(priv->subtitle_font), 12,
				temp);
		pango_layout_get_pixel_size(layout, &layout_w, &layout_h);
		max_width = max_width > layout_w ? max_width : layout_w;
		total_heigh += layout_h;
		cairo_move_to(cr, (w - layout_w) / 2., 0);
		pango_cairo_show_layout(cr, layout);
		cairo_move_to(cr, (w - layout_w) / 2., 0);
		pango_cairo_layout_path(cr, layout);
		cairo_set_source_rgba(cr, stroke_color.red, stroke_color.green,
				stroke_color.blue, stroke_color.alpha);
		cairo_stroke(cr);
		g_object_unref(layout);
		cairo_translate(cr, 0, layout_h);
		g_free(temp);
		p += 5;
		s = p;
		p = g_strstr_len(s, -1, "</br>");
	}
	temp = g_strdup(s);
	layout = my_subtitle_parse_srt_text_line(cr, &font_color,
			gtk_font_chooser_get_font_family(priv->subtitle_font), 12, temp);
	pango_layout_get_pixel_size(layout, &layout_w, &layout_h);
	max_width = max_width > layout_w ? max_width : layout_w;
	total_heigh += layout_h;
	cairo_move_to(cr, (w - layout_w) / 2., 0);
	pango_cairo_show_layout(cr, layout);
	cairo_move_to(cr, (w - layout_w) / 2., 0);
	pango_cairo_layout_path(cr, layout);
	cairo_set_source_rgba(cr, stroke_color.red, stroke_color.green,
			stroke_color.blue, stroke_color.alpha);
	cairo_stroke(cr);
	g_object_unref(layout);
	g_free(temp);

	result = gdk_pixbuf_get_from_surface(surf, (w - max_width) / 2.0, 0,
			max_width, total_heigh);
	cairo_destroy(cr);
	cairo_surface_destroy(surf);
	return result;
}

guint64 my_main_win_add_subtitle(MyMainWin *self, gdouble start, gdouble end,
		gchar *subtitle) {
	if (subtitle == NULL)
		return 0;
	gint w, h;
	gchar *s, *p, *temp;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gchar *describe = g_strdup_printf("%d", priv->subtitle_index);
	GtkTreeIter iter;
	GdkRGBA color;
	color.red = 0.2;
	color.green = 1.0;
	color.blue = 0.5;
	color.alpha = 0.9;

	//add to the trace bar
	my_trace_bar_add_obj_range(priv->trace_bar,
			GUINT_TO_POINTER(priv->subtitle_index), start, end, describe,
			&color);
	g_free(describe);

	//add to the subtitle_list for the treeview
	gtk_list_store_append(priv->subtitle_list, &iter);
	gtk_list_store_set(priv->subtitle_list, &iter, col_index,
			priv->subtitle_index, col_start, start, col_end, end, col_text,
			subtitle, -1);
	s = g_strdup_printf(SUBTITLE_LIST_TIME_FORMAT, start);
	p = g_strdup_printf(SUBTITLE_LIST_TIME_FORMAT, end);
	GdkPixbuf *pixbuf = my_main_win_gen_subtitle_preview(self, subtitle);
	gtk_list_store_set(priv->subtitle_list, &iter, col_start_text, s,
			col_end_text, p, col_preview, pixbuf, -1);
	g_free(s);
	g_free(p);
	gdk_pixbuf_unref(pixbuf);
	//add to table
	SubtitleDictData *data = malloc(sizeof(SubtitleDictData));
	data->index = priv->subtitle_index;
	data->subtitle = g_strdup(subtitle);
	GtkTreePath *path = gtk_tree_model_get_path(priv->subtitle_list, &iter);
	data->ref = gtk_tree_row_reference_new(priv->subtitle_list, path);
	gtk_tree_path_free(path);
	g_hash_table_insert(priv->subtitle_table,
			GUINT_TO_POINTER(priv->subtitle_index), data);
	priv->subtitle_index++;
	return 0;
}

void add_subtitle_cb(GtkButton *button, MyMainWin *self) {
	gdouble current_pos, last_time;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	current_pos = my_trace_bar_get_value(priv->trace_bar);
	last_time = gtk_spin_button_get_value(priv->subtitle_last_time);
	my_main_win_add_subtitle(self, current_pos, current_pos + last_time,
			gtk_entry_get_text(priv->subtitle));

	//reset to default state.
	gtk_entry_set_text(priv->subtitle, "\0");
	gtk_spin_button_set_value(priv->subtitle_last_time,
			gtk_spin_button_get_value(priv->default_subtitle_last_time));
	gst_element_set_state(priv->pipeline, priv->cur_state);
}

void subtitle_auto_pause(GtkEntry *entry, gchar *new_text, gint new_text_length,
		gpointer position, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gboolean auto_pause = gtk_toggle_button_get_active(priv->auto_pause);
	if (auto_pause == TRUE)
		gst_element_set_state(priv->pipeline, GST_STATE_PAUSED);
}

void my_main_win_del_subtitle(MyMainWin *self, guint64 index) {
	GtkTreeIter iter;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gpointer p = GUINT_TO_POINTER(index);
	my_trace_bar_del_obj_range(priv->trace_bar, p);
	SubtitleDictData *data = g_hash_table_lookup(priv->subtitle_table, p);
	//remove from subtitle_list in treeview
	if (my_main_win_tree_row_ref_get_iter(data->ref, &iter)) {
		gtk_list_store_remove(priv->subtitle_list, &iter);
	}
	gtk_tree_row_reference_free(data->ref);
	//remove from trace bar
	my_trace_bar_del_obj_range(priv->trace_bar, p);
	//remove from subtitle table
	g_hash_table_remove(priv->subtitle_table, p);
	//release the data from memory
	g_free(data->subtitle);
	g_free(data);

}

void pop_menu_del_cb(GtkButton *button, MyMainWin *self) {
	GtkTreeIter iter;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	my_main_win_del_subtitle(self, GPOINTER_TO_UINT(priv->selected_index));
	priv->selected_index = NULL;
	gtk_popover_popdown(priv->pop_menu);
}

void pop_menu_color_color_set_cb(GtkColorButton *widget, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GdkRGBA color;
	gtk_color_chooser_get_rgba(priv->pop_menu_color, &color);
	my_trace_bar_set_obj_color(priv->trace_bar, priv->selected_index, &color);
}

void pop_menu_subtitle_activate_cb(GtkEntry *entry, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	SubtitleDictData *data = g_hash_table_lookup(priv->subtitle_table,
			priv->selected_index);
	g_free(data->subtitle);
	data->subtitle = g_strdup(gtk_entry_get_text(entry));
	subtitle_list_sync_data(self, priv->selected_index);

}

void pop_menu_start_change_value_cb(GtkSpinButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gdouble end, start;
	my_trace_bar_get_obj_range(priv->trace_bar, priv->selected_index, &start,
			&end);
	start = gtk_spin_button_get_value(priv->pop_menu_start);
	my_trace_bar_set_obj_range(priv->trace_bar, priv->selected_index, start,
			end);
	subtitle_list_sync_data(self, priv->selected_index);
}

void pop_menu_end_change_value_cb(GtkSpinButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gdouble end, start;
	my_trace_bar_get_obj_range(priv->trace_bar, priv->selected_index, &start,
			&end);
	end = gtk_spin_button_get_value(priv->pop_menu_end);
	my_trace_bar_set_obj_range(priv->trace_bar, priv->selected_index, start,
			end);
	subtitle_list_sync_data(self, priv->selected_index);
}

void pop_menu_label_activate_cb(GtkEntry *entry, MyMainWin *self) {
	gchar *text;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	text = gtk_entry_get_text(priv->pop_menu_label);
	my_trace_bar_set_obj_describe(priv->trace_bar, priv->selected_index, text);
}

void pop_menu_sync(MyMainWin *self, gpointer index) {
	GdkRGBA *color;
	gdouble s, e;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	SubtitleDictData *data = g_hash_table_lookup(priv->subtitle_table, index);
	my_trace_bar_get_obj_range(priv->trace_bar, index, &s, &e);
	color = my_trace_bar_get_obj_color(priv->trace_bar, index);
	gchar *describe = my_trace_bar_get_obj_describe(priv->trace_bar, index);
	gtk_spin_button_set_value(priv->pop_menu_start, s);
	gtk_spin_button_set_value(priv->pop_menu_end, e);
	gtk_entry_set_text(priv->pop_menu_subtitle, data->subtitle);
	gtk_entry_set_text(priv->pop_menu_label, describe);
	gtk_color_chooser_set_rgba(priv->pop_menu_color, color);
}

void ex_popover_popup_down_cb(GtkButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	if (button == priv->ex_menu) {
		gtk_popover_set_relative_to(priv->ex_popover, priv->subtitle);
	} else {
		gtk_popover_set_relative_to(priv->ex_popover, priv->pop_menu_subtitle);
	}
	gboolean visual = gtk_widget_is_visible(priv->ex_popover);
	if (visual) {
		gtk_popover_popdown(priv->ex_popover);
	} else {
		gtk_popover_popup(priv->ex_popover);
	}
}

void subtitle_color_set_cb(GtkColorButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gint s = 0, e = 0, len, ns, ne;
	gchar *text;
	GdkRGBA color;
	GString *temp = g_string_new("");
	GtkEntry *entry = gtk_popover_get_relative_to(priv->ex_popover);
	gtk_color_chooser_get_rgba(priv->subtitle_color, &color);
	gtk_editable_get_selection_bounds(entry, &s, &e);
	if (s > e) {
		len = s;
		s = e;
		e = len;
	}
	len = e - s;
	text = gtk_editable_get_chars(entry, 0, s);
	temp = g_string_append(temp, text);
	g_free(text);
	guint r = color.red * 255;
	guint g = color.green * 255;
	guint b = color.blue * 255;
	g_string_append_printf(temp, "<font color=\"#%02x%02x%02x\">", r, g, b);
	ns = g_utf8_strlen(temp->str, -1);
	text = gtk_editable_get_chars(entry, s, e);
	temp = g_string_append(temp, text);
	g_free(text);
	ne = g_utf8_strlen(temp->str, -1);
	g_string_append_printf(temp, "</font>");
	text = gtk_editable_get_chars(entry, e, -1);
	temp = g_string_append(temp, text);
	g_free(text);
	gtk_entry_set_text(entry, temp->str);
	gtk_editable_select_region(entry, ns, ne);
	g_string_free(temp, TRUE);
}

void subtitle_bold_cb(GtkButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gint s = 0, e = 0, len, ns, ne;
	gchar *text;
	GString *temp = g_string_new("");
	GtkEntry *entry = gtk_popover_get_relative_to(priv->ex_popover);
	gtk_editable_get_selection_bounds(entry, &s, &e);
	if (s > e) {
		len = s;
		s = e;
		e = len;
	}
	len = e - s;
	text = gtk_editable_get_chars(entry, 0, s);
	temp = g_string_append(temp, text);
	g_free(text);
	g_string_append_printf(temp, "<b>");
	ns = g_utf8_strlen(temp->str, -1);
	text = gtk_editable_get_chars(entry, s, e);
	temp = g_string_append(temp, text);
	g_free(text);
	ne = g_utf8_strlen(temp->str, -1);
	g_string_append_printf(temp, "</b>");
	text = gtk_editable_get_chars(entry, e, -1);
	temp = g_string_append(temp, text);
	g_free(text);
	gtk_entry_set_text(entry, temp->str);
	gtk_editable_select_region(entry, ns, ne);
	g_string_free(temp, TRUE);
}

void subtitle_italic_cb(GtkButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gint s = 0, e = 0, len, ns, ne;
	gchar *text;
	GString *temp = g_string_new("");
	GtkEntry *entry = gtk_popover_get_relative_to(priv->ex_popover);
	gtk_editable_get_selection_bounds(entry, &s, &e);
	if (s > e) {
		len = s;
		s = e;
		e = len;
	}
	len = e - s;
	text = gtk_editable_get_chars(entry, 0, s);
	temp = g_string_append(temp, text);
	g_free(text);
	g_string_append_printf(temp, "<i>");
	ns = g_utf8_strlen(temp->str, -1);
	text = gtk_editable_get_chars(entry, s, e);
	temp = g_string_append(temp, text);
	g_free(text);
	ne = g_utf8_strlen(temp->str, -1);
	g_string_append_printf(temp, "</i>");
	text = gtk_editable_get_chars(entry, e, -1);
	temp = g_string_append(temp, text);
	g_free(text);
	gtk_entry_set_text(entry, temp->str);
	gtk_editable_select_region(entry, ns, ne);
	g_string_free(temp, TRUE);
}

void subtitle_under_line_cb(GtkButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gint s = 0, e = 0, len, ns, ne;
	gchar *text;
	GString *temp = g_string_new("");
	GtkEntry *entry = gtk_popover_get_relative_to(priv->ex_popover);
	gtk_editable_get_selection_bounds(entry, &s, &e);
	if (s > e) {
		len = s;
		s = e;
		e = len;
	}
	len = e - s;
	text = gtk_editable_get_chars(entry, 0, s);
	temp = g_string_append(temp, text);
	g_free(text);
	g_string_append_printf(temp, "<u>");
	ns = g_utf8_strlen(temp->str, -1);
	text = gtk_editable_get_chars(entry, s, e);
	temp = g_string_append(temp, text);
	g_free(text);
	ne = g_utf8_strlen(temp->str, -1);
	g_string_append_printf(temp, "</u>");
	text = gtk_editable_get_chars(entry, e, -1);
	temp = g_string_append(temp, text);
	g_free(text);
	gtk_entry_set_text(entry, temp->str);
	gtk_editable_select_region(entry, ns, ne);
	g_string_free(temp, TRUE);
}

void subtitle_add_br_cb(GtkButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gint s = 0, e = 0, len, ns, ne;
	gchar *text;
	GString *temp = g_string_new("");
	GtkEntry *entry = gtk_popover_get_relative_to(priv->ex_popover);
	g_object_get(entry, "cursor-position", &s, "selection-bound", &e, "text",
			&text, NULL);
	if (s > e) {
		len = s;
		s = e;
		e = len;
	}
	len = e - s;
	temp = g_string_append_len(temp, text, s);
	g_string_append_printf(temp, "</br>");
	ns = temp->len;
	ne = ns + len;
	temp = g_string_append_len(temp, text + s, len);
	temp = g_string_append(temp, text + e);
	gtk_entry_set_text(entry, temp->str);
	gtk_editable_select_region(entry, ns, ne);
	g_string_free(temp, TRUE);
	g_free(text);
}

void subtitle_add_special_char_cb(GtkButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gint s;
	gchar *text = gtk_button_get_label(button);
	GtkEntry *entry = gtk_popover_get_relative_to(priv->ex_popover);
	g_object_get(entry, "cursor-position", &s, NULL);
	gtk_editable_insert_text(entry, text, -1, &s);
	gtk_editable_set_position(entry, s);
}

gboolean subtitle_list_draw_cb(GtkWidget *widget, cairo_t *cr, MyMainWin *self) {
	GList *list, *unlist;
	SubtitleDictData *data;
	list = NULL;
	unlist = NULL;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	my_trace_bar_get_active_object(priv->trace_bar, &list, &unlist);
	list = g_list_first(list);
	unlist = g_list_first(unlist);
	GHashTableIter iter;
	GtkTreeIter titer;
	//set the unactive state in subtitle list in treeview
	while (unlist->data != NULL) {
		data = g_hash_table_lookup(priv->subtitle_table, unlist->data);
		my_main_win_tree_row_ref_get_iter(data->ref, &titer);
		gtk_list_store_set(priv->subtitle_list, &titer, col_active, "", -1);
		unlist = unlist->next;
	}
	g_list_free(unlist);
	//set the active state in subtitle list in treeview
	while (list->data != NULL) {
		data = g_hash_table_lookup(priv->subtitle_table, list->data);
		my_main_win_tree_row_ref_get_iter(data->ref, &titer);
		gtk_list_store_set(priv->subtitle_list, &titer, col_active,
				"media-playback-start-symbolic", -1);
		list = list->next;
	}
	g_list_free(list);
	return FALSE;
}

void subtitle_list_set_active(GtkCellRendererToggle *cell_renderer, gchar *path,
		MyMainWin *self) {
	g_print("set active\n");
}

void subtitle_list_set_start(GtkCellRendererText *renderer, gchar *path,
		gchar *new_text, MyMainWin *self) {
	guint64 index;
	gdouble s, e;
	gchar *start_text;
	GtkTreeIter iter;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GtkTreePath *tpath = gtk_tree_path_new_from_string(path);
	gtk_tree_model_get_iter(priv->subtitle_list, &iter, tpath);
	gtk_tree_path_free(tpath);
	s = atof(new_text);
	gtk_tree_model_get(priv->subtitle_list, &iter, col_index, &index, col_end,
			&e, -1);
	if (s > e)
		s = e;
	start_text = g_strdup_printf(SUBTITLE_LIST_TIME_FORMAT, s);
	gtk_list_store_set(priv->subtitle_list, &iter, col_start, s, col_start_text,
			start_text, -1);
	g_free(start_text);
	my_trace_bar_set_obj_range(priv->trace_bar, GUINT_TO_POINTER(index), s, e);
	if (priv->selected_index == GUINT_TO_POINTER(index))
		pop_menu_sync(self, GUINT_TO_POINTER(index));
}

void subtitle_list_set_end(GtkCellRendererText *renderer, gchar *path,
		gchar *new_text, MyMainWin *self) {
	guint64 index;
	gdouble s, e;
	gchar *end_text;
	GtkTreeIter iter;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GtkTreePath *tpath = gtk_tree_path_new_from_string(path);
	gtk_tree_model_get_iter(priv->subtitle_list, &iter, tpath);
	gtk_tree_path_free(tpath);
	e = atof(new_text);
	gtk_tree_model_get(priv->subtitle_list, &iter, col_index, &index, col_start,
			&s, -1);
	if (s > e)
		e = s;
	end_text = g_strdup_printf(SUBTITLE_LIST_TIME_FORMAT, e);
	gtk_list_store_set(priv->subtitle_list, &iter, col_end, e, col_end_text,
			end_text, -1);
	g_free(end_text);
	my_trace_bar_set_obj_range(priv->trace_bar, GUINT_TO_POINTER(index), s, e);
	if (priv->selected_index == GUINT_TO_POINTER(index))
		pop_menu_sync(self, GUINT_TO_POINTER(index));
}

void subtitle_list_set_text(GtkCellRendererText *renderer, gchar *path,
		gchar *new_text, MyMainWin *self) {
	guint64 index;
	GtkTreeIter iter;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GtkTreePath *tpath = gtk_tree_path_new_from_string(path);
	gtk_tree_model_get_iter(priv->subtitle_list, &iter, tpath);
	gtk_tree_path_free(tpath);
	gtk_tree_model_get(priv->subtitle_list, &iter, col_index, &index, -1);
	GdkPixbuf *pixbuf = my_main_win_gen_subtitle_preview(self, new_text);
	gtk_list_store_set(priv->subtitle_list, &iter, col_text, new_text,
			col_preview, pixbuf, -1);
	SubtitleDictData *data = g_hash_table_lookup(priv->subtitle_table,
			GUINT_TO_POINTER(index));
	g_free(data->subtitle);
	data->subtitle = g_strdup(new_text);
	gdk_pixbuf_unref(pixbuf);
	if (priv->selected_index == GUINT_TO_POINTER(index))
		pop_menu_sync(self, GUINT_TO_POINTER(index));
}

void subtitle_list_sync_data(MyMainWin *self, gpointer index) {
	if(index==NULL)return;
	gdouble s, e;
	gchar *s_text, *e_text;
	GtkTreeIter iter;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	SubtitleDictData *data = g_hash_table_lookup(priv->subtitle_table, index);
	gchar *subtitle = data->subtitle;
	my_trace_bar_get_obj_range(priv->trace_bar, index, &s, &e);
	s_text = g_strdup_printf(SUBTITLE_LIST_TIME_FORMAT, s);
	e_text = g_strdup_printf(SUBTITLE_LIST_TIME_FORMAT, e);
	GdkPixbuf *pixbuf = my_main_win_gen_subtitle_preview(self, data->subtitle);
	my_main_win_tree_row_ref_get_iter(data->ref, &iter);
	gtk_list_store_set(priv->subtitle_list, &iter, col_start, s, col_start_text,
			s_text, col_end, e, col_end_text, e_text, col_preview, pixbuf,
			col_text, data->subtitle, -1);
	g_free(s_text);
	g_free(e_text);
	gdk_pixbuf_unref(pixbuf);
}

void subtitle_list_popup_down_cb(GtkButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GtkPopover *popover = priv->pop_subtitle_list;
	if (gtk_widget_is_visible(popover)) {
		gtk_popover_popdown(popover);
	} else {
		gtk_popover_popup(popover);
	}
}

void subtitle_list_del_cb(GtkButton *button, MyMainWin *self) {
	guint64 index;
	GList *index_list = NULL;
	GtkTreeIter iter;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GtkTreeSelection *sel = gtk_tree_view_get_selection(
			priv->subtitle_treeview);
	GList *list = gtk_tree_selection_get_selected_rows(sel,
			&priv->subtitle_list);
	GList *p = list;
	while (p != NULL) {
		gtk_tree_model_get_iter(priv->subtitle_list, &iter, p->data);
		gtk_tree_model_get(priv->subtitle_list, &iter, col_index, &index, -1);
		index_list = g_list_append(index_list, GUINT_TO_POINTER(index));
		p = p->next;
	}
	p = index_list;
	while (p != NULL) {
		index = GPOINTER_TO_UINT(p->data);
		my_main_win_del_subtitle(self, index);
		p = p->next;
	}
	g_list_free(index_list);
	g_list_free_full(list, gtk_tree_path_free);
}

void subtitle_edit(MyMainWin *self) {
	GtkTreeIter iter;
	guint64 index;
	gint s_text,e_text,p_text;
	gdouble s, e, second;
	GtkTreePath *path = gtk_tree_path_new_first();
	GMatchInfo *info;
	gchar *text, *match_pattern, *temp;
	GString *new_text;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gchar *pattern = gtk_entry_get_text(priv->subtitle_list_edit_pattern);
	gchar *format;
	GRegex *regex;
	if(g_strcmp0(pattern,"")==0){
		regex = g_regex_new(".+", 0, 0, NULL);
	}else{
		regex = g_regex_new(pattern, 0, 0, NULL);
	}

	GDateTime *datetime = g_date_time_new_now_local();
	while (gtk_tree_model_get_iter(priv->subtitle_list_edit_preview, &iter,
			path)) {
		gtk_tree_model_get(priv->subtitle_list_edit_preview, &iter,
				col_edit_preview_index, &index, col_edit_preview_beforce, &text,
				-1);
		my_trace_bar_get_obj_range(priv->trace_bar, GUINT_TO_POINTER(index), &s,
				&e);
		format= g_strdup(gtk_entry_get_text(priv->subtitle_list_edit_format));
		new_text=g_string_new("");
		if (g_strstr_len(format, -1, "%sh")) {
			temp = g_strdup_printf("%02d", (gint)s / 3600);
			string_replace(&format, "%sh", temp);
			g_free(temp);
		};
		s = s - (gint)(s / 3600) * 3600;
		if (g_strstr_len(format, -1, "%sm")) {
			temp = g_strdup_printf("%02d", (gint)s / 60);
			string_replace(&format, "%sm", temp);
			g_free(temp);
		};
		s = s - (gint)(s / 60) * 60;
		if (g_strstr_len(format, -1, "%ss")) {
			temp = g_strdup_printf("%06.3lf", s);
			string_replace(&format, "%ss", temp);
			g_free(temp);
		};
		if (g_strstr_len(format, -1, "%eh")) {
			temp = g_strdup_printf("%02d", (gint)e / 3600);
			string_replace(&format, "%eh", temp);
			g_free(temp);
		};
		e = e -(gint)(e / 3600) * 3600;
		if (g_strstr_len(format, -1, "%em")) {
			temp = g_strdup_printf("%02d", (gint)e / 60);
			string_replace(&format, "%em", temp);
			g_free(temp);
		};
		e = e - (gint)(e / 60) * 60;
		if (g_strstr_len(format, -1, "%es")) {
			temp = g_strdup_printf("%06.3lf", e);
			string_replace(&format, "%es", temp);
			g_free(temp);
		};

		if (g_strstr_len(format, -1, "%rhh")) {
			temp = g_strdup_printf("%02d", g_date_time_get_hour(datetime));
			string_replace(&format, "%rhh", temp);
			g_free(temp);
		};
		if (g_strstr_len(format, -1, "%rmm")) {
			temp = g_strdup_printf("%02d", g_date_time_get_minute(datetime));
			string_replace(&format, "%rmm", temp);
			g_free(temp);
		};
		if (g_strstr_len(format, -1, "%rss")) {
			temp = g_strdup_printf("%02d", g_date_time_get_second(datetime));
			string_replace(&format, "%rss", temp);
			g_free(temp);
		};
		if (g_strstr_len(format, -1, "%d")) {
			temp = g_strdup_printf("%02d",
					g_date_time_get_day_of_month(datetime));
			string_replace(&format, "%d", temp);
			g_free(temp);
		};
		if (g_strstr_len(format, -1, "%m")) {
			temp = g_strdup_printf("%02d", g_date_time_get_month(datetime));
			string_replace(&format, "%m", temp);
			g_free(temp);
		};
		if (g_strstr_len(format, -1, "%y")) {
			temp = g_strdup_printf("%d", g_date_time_get_year(datetime));
			string_replace(&format, "%y", temp);
			g_free(temp);
		};
		p_text=0;
		g_regex_match(regex, text, 0, &info);
		while (g_match_info_matches(info)) {
			g_match_info_fetch_pos(info,0,&s_text,&e_text);
			g_string_append_len(new_text,text+p_text,s_text-p_text);
			p_text=e_text;
			if (g_strstr_len(format, -1, "%p")) {
				match_pattern=g_match_info_fetch(info,0);
				temp=string_replace_not_free(format,"%p",match_pattern);
				g_string_append_printf(new_text,"%s",temp);
				g_free(temp);
				g_free(match_pattern);
			}else{
				g_string_append_printf(new_text,"%s",format);
			};
			g_match_info_next(info, NULL);
		}
		g_string_append_printf(new_text,"%s",text+p_text);
		gtk_list_store_set(priv->subtitle_list_edit_preview,&iter,col_edit_preview_after,new_text->str,-1);
		g_string_free(new_text,TRUE);
		g_match_info_free(info);
		g_free(text);
		g_free(format);
		gtk_tree_path_next(path);
	}
	g_date_time_unref(datetime);
	g_regex_unref(regex);
}

void subtitle_list_edit_cb(GtkButton *button, MyMainWin *self) {
	guint64 index;
	GtkTreeIter iter, piter;
	SubtitleDictData *data;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GtkTreeSelection *sel = gtk_tree_view_get_selection(
			priv->subtitle_treeview);
	GList *list = gtk_tree_selection_get_selected_rows(sel,
			&priv->subtitle_list);
	gtk_list_store_clear(priv->subtitle_list_edit_preview);
	while (1) {
		gtk_tree_model_get_iter(priv->subtitle_list, &iter, list->data);
		gtk_tree_model_get(priv->subtitle_list, &iter, col_index, &index, -1);
		data = g_hash_table_lookup(priv->subtitle_table,
				GUINT_TO_POINTER(index));
		gtk_list_store_append(priv->subtitle_list_edit_preview, &piter);
		gtk_list_store_set(priv->subtitle_list_edit_preview, &piter,
				col_edit_preview_index, index, col_edit_preview_beforce,
				data->subtitle, -1);
		if (list->next == NULL)
			break;
		list = list->next;
	}
	g_list_free_full(list, gtk_tree_path_free);
	gint respon = gtk_dialog_run(priv->subtitle_list_edit_dialog);
	gtk_widget_hide(priv->subtitle_list_edit_dialog);
	if (respon == GTK_RESPONSE_CANCEL)return;
	subtitle_edit(self);
	GtkTreePath *path=gtk_tree_path_new_first();
	gchar *after;
	while(gtk_tree_model_get_iter(priv->subtitle_list_edit_preview,&iter,path)){
		gtk_tree_model_get(priv->subtitle_list_edit_preview,&iter,col_edit_preview_index,&index,col_edit_preview_after,&after,-1);
		data=g_hash_table_lookup(priv->subtitle_table,GUINT_TO_POINTER(index));
		g_free(data->subtitle);
		data->subtitle=after;
		pop_menu_sync(self,GUINT_TO_POINTER(index));
		subtitle_list_sync_data(self,GUINT_TO_POINTER(index));
		gtk_tree_path_next(path);
	};
	gtk_tree_path_free(path);

}

void subtitle_list_open_cb(GtkButton *button, MyMainWin *self) {
	gdouble s, e;
	gchar *text;
	GtkFileChooserDialog *dialog = gtk_file_chooser_dialog_new(
			"Open Subtitle File", self, GTK_FILE_CHOOSER_ACTION_OPEN,
			GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
			GTK_RESPONSE_CANCEL, NULL);
	gint respon = gtk_dialog_run(dialog);
	if (respon == GTK_RESPONSE_OK) {
		gchar *location = gtk_file_chooser_get_filename(dialog);
		MySubtitle *subtitle = my_srt_subtitle_new();
		my_subtitle_load_file(subtitle, location);
		guint64 count = my_subtitle_get_total_size(subtitle);
		for (guint64 i = 1; i <= count; i++) {
			text = my_subtitle_get_subtitle(subtitle, i, &s, &e,
					Subtitle_Format_None);
			my_main_win_add_subtitle(self, s, e, text);
		}
		g_object_unref(subtitle);
		g_free(location);
	}
	gtk_widget_destroy(dialog);
}

void subtitle_list_save_cb(GtkButton *button, MyMainWin *self) {
	gdouble start, end;
	gchar *subtitle;
	SubtitleDictData *data;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GtkFileChooserDialog *dialog = gtk_file_chooser_dialog_new(
			"Save Subtitle File", self, GTK_FILE_CHOOSER_ACTION_SAVE,
			GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
			GTK_RESPONSE_CANCEL, NULL);
	gint respon = gtk_dialog_run(dialog);
	if (respon == GTK_RESPONSE_OK) {
		gchar *location = gtk_file_chooser_get_filename(dialog);
		MySubtitle *subtitle = my_srt_subtitle_new();
		GList *key = g_hash_table_get_keys(priv->subtitle_table);
		if (key != NULL) {
			while (1) {
				data = g_hash_table_lookup(priv->subtitle_table,
						GUINT_TO_POINTER(key->data));
				my_trace_bar_get_obj_range(priv->trace_bar,
						GUINT_TO_POINTER(data->index), &start, &end);
				my_subtitle_add_subtitle(subtitle, data->subtitle, start, end,
						Subtitle_Format_None);
				if (key->next != NULL)
					key = key->next;
				else
					break;
			}
			g_list_free(key);
			my_subtitle_to_file(subtitle, location);
		}
		g_free(location);
		g_object_unref(subtitle);
	}
	gtk_widget_destroy(dialog);
}

void subtitle_list_find_next_cb(GtkButton *button, MyMainWin *self) {
	GList *list=NULL;
	GtkTreePath *path;
	GtkTreeIter iter;
	gchar *text,*find_parttern;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GtkTreeSelection *sel = gtk_tree_view_get_selection(
			priv->subtitle_treeview);
	guint count = gtk_tree_selection_count_selected_rows(sel);
	find_parttern=gtk_entry_get_text(priv->find_entry);
	switch (count){
	case 0:
		path = gtk_tree_path_new_first();
		break;
	default:
		list=gtk_tree_selection_get_selected_rows(sel,&priv->subtitle_list);
		path=list->data;
		while(1){
			if(list->next==NULL)break;
			list=list->next;
			if(gtk_tree_path_compare(list->data,path)>0)
				path=list->data;
		}
		break;
	}
	while(gtk_tree_model_get_iter(priv->subtitle_list,&iter,path)){
		gtk_tree_model_get(priv->subtitle_list,&iter,col_text,&text,-1);
		if(g_strstr_len(text,-1,find_parttern)!=NULL){
			gtk_tree_selection_unselect_all(sel);
			gtk_tree_selection_select_path(sel,path);
			g_free(text);
			break;
		};
		g_free(text);
		gtk_tree_path_next(path);
	}
	if(list!=NULL)
		g_list_free_full(list,gtk_tree_path_free);
	else
		gtk_tree_path_free(path);
}

void subtitle_list_find_before_cb(GtkButton *button, MyMainWin *self) {
	GList *list=NULL;
	GtkTreePath *path;
	GtkTreeIter iter;
	gchar *text,*find_parttern;
	gint depth;
	gchar *temp;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GtkTreeSelection *sel = gtk_tree_view_get_selection(
			priv->subtitle_treeview);
	guint count = gtk_tree_selection_count_selected_rows(sel);
	find_parttern=gtk_entry_get_text(priv->find_entry);
	switch (count){
	case 0:
		path = gtk_tree_path_new_first();
		depth=gtk_tree_path_get_depth (path);
		gtk_tree_path_free(path);
		temp=g_strdup_printf("%d",depth);
		gtk_tree_path_new_from_string(temp);
		g_free(temp);
		break;
	default:
		list=gtk_tree_selection_get_selected_rows(sel,&priv->subtitle_list);
		path=list->data;
		while(1){
			if(list->next==NULL)break;
			list=list->next;
			if(gtk_tree_path_compare(list->data,path)<0)
				path=list->data;
		}
		break;
	}
	while(gtk_tree_model_get_iter(priv->subtitle_list,&iter,path)){
		gtk_tree_model_get(priv->subtitle_list,&iter,col_text,&text,-1);
		if(g_strstr_len(text,-1,find_parttern)!=NULL){
			gtk_tree_selection_unselect_all(sel);
			gtk_tree_selection_select_path(sel,path);
			g_free(text);
			break;
		};
		g_free(text);
		if(gtk_tree_path_prev(path)!=TRUE)break;
	}

	if(list!=NULL)
		g_list_free_full(list,gtk_tree_path_free);
	else
		gtk_tree_path_free(path);
}

void subtitle_list_selection_cb(GtkTreeSelection *treeselection,
		MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gint count = gtk_tree_selection_count_selected_rows(treeselection);
	if (count > 1)
		gtk_widget_set_sensitive(priv->subtitle_list_edit, TRUE);
	else
		gtk_widget_set_sensitive(priv->subtitle_list_edit, FALSE);
}

void my_main_win_trace_bar_obj_selected(MyTraceBar *bar, gpointer index,
		GdkRectangle *rectangle, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	priv->selected_index = index;
	pop_menu_sync(self, index);
	gtk_popover_set_relative_to(priv->pop_menu, bar);
	gtk_popover_set_pointing_to(priv->pop_menu, rectangle);
	gtk_popover_popup(priv->pop_menu);

}
gboolean pop_label_preview_draw_callback(GtkDrawingArea *pop_label_preview,
		cairo_t *cr, MyMainWin *self) {
	GdkPixbuf *pixbuf = g_object_get_data(pop_label_preview, "pixbuf");
	if (pixbuf == NULL)
		return TRUE;
	gint w, h;
	w = gdk_pixbuf_get_width(pixbuf);
	h = gdk_pixbuf_get_height(pixbuf);
	gtk_widget_set_size_request(pop_label_preview, w, h);
	gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
	cairo_paint(cr);
	return TRUE;
}
void my_main_win_trace_bar_obj_preselected(MyTraceBar *bar, gpointer index,
		GdkRectangle *rectangle, MyMainWin *self) {
	GtkTreeIter iter;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	SubtitleDictData *data = g_hash_table_lookup(priv->subtitle_table, index);
	my_main_win_tree_row_ref_get_iter(data->ref, &iter);
	GdkPixbuf *pixbuf = NULL;
	gtk_tree_model_get(priv->subtitle_list, &iter, col_preview, &pixbuf, -1);
	if (pixbuf != NULL)
		g_object_set_data(priv->pop_label_preview, "pixbuf", pixbuf);
	gtk_label_set_text(priv->pop_label_text, data->subtitle);
	gtk_popover_set_relative_to(priv->pop_label, bar);
	gtk_popover_set_pointing_to(priv->pop_label, rectangle);
	gtk_popover_popup(priv->pop_label);
}

void my_main_win_trace_bar_obj_unpreselected(MyTraceBar *bar, gpointer obj,
		MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gtk_popover_popdown(priv->pop_label);
}

void my_main_win_trace_bar_obj_unselected(MyTraceBar *bar, gpointer obj,
		MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gtk_popover_popdown(priv->pop_menu);
	priv->selected_index = NULL;
}

void my_main_win_trace_bar_obj_range_change(MyTraceBar *bar, gpointer index,
		gdouble start, gdouble end, MyMainWin *self) {
	GtkTreeIter iter;
	SubtitleDictData *data;
	gchar *start_text, *end_text;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);

//update the subtitle_list in the treeview
	start_text = g_strdup_printf(SUBTITLE_LIST_TIME_FORMAT, start);
	end_text = g_strdup_printf(SUBTITLE_LIST_TIME_FORMAT, end);
	data = g_hash_table_lookup(priv->subtitle_table, GUINT_TO_POINTER(index));
	my_main_win_tree_row_ref_get_iter(data->ref, &iter);
	gtk_list_store_set(priv->subtitle_list, &iter, col_start, start,
			col_start_text, start_text, col_end, end, col_end_text, end_text,
			-1);
	g_free(start_text);
	g_free(end_text);

	if (priv->selected_index != index)
		return;
	gtk_spin_button_set_value(priv->pop_menu_start, start);
	gtk_spin_button_set_value(priv->pop_menu_end, end);

}

gboolean info_bar_close_cb(MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	priv->info_timeout--;
	if (priv->info_timeout != 0)
		return G_SOURCE_CONTINUE;
	gtk_info_bar_set_revealed(priv->info_bar, FALSE);
	return G_SOURCE_REMOVE;
}

void my_main_win_info_bar_show_info(MyMainWin *self, guchar timeout, gchar *fmt,
		...) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	va_list ap;
	va_start(ap, fmt);
	gchar *message = g_strdup_vprintf(fmt, ap);
	va_end(ap);
	gtk_label_set_text(priv->info_message, message);
	if (priv->info_timeout == 0)
		g_timeout_add(1000, info_bar_close_cb, self);
	priv->info_timeout = timeout;
	gtk_info_bar_set_revealed(priv->info_bar, TRUE);
//gtk_widget_show_all(priv->info_bar);
	g_free(message);
}

gpointer subtitle_normal_color[][4] = { { "red", 255, 0, 0 }, { "green", 0, 255,
		0 }, { "blue", 0, 0, 255 }, { "yellow", 255, 255, 0 }, { "purple", 255,
		0, 255 }, { "cyan", 0, 255, 255 }, { "white", 255, 255, 255 }, { NULL,
		0, 0, 0 },
NULL, };

void print_font_describe(PangoLayout *layout) {
	gchar *des;
	PangoFontDescription *desc = pango_layout_get_font_description(layout);
	des = pango_font_description_to_string(desc);
	g_print("%s \ttext:%s\n", des, pango_layout_get_text(layout));
	g_free(des);
}

gboolean content_draw_cb(GtkDrawingArea *content, cairo_t *cr, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gint w, h, n_subtitle, rows;
	gchar *br = NULL, *pbr = NULL;
	gfloat radio;
	gint64 dur, pos;
	GList *list, *unlist, *list_row = NULL;
	gint text_height, text_width, text_num, text_x, text_y;
	GdkRGBA stroke_color, fill_color;
	PangoLayout *text_layout;
	gpointer key;
	SubtitleDictData *data;
	gint ch = gtk_widget_get_allocated_height(priv->content);
	gint cw = gtk_widget_get_allocated_width(priv->content);

	cairo_save(cr);
	cairo_set_source_rgb(cr, 0., 0., 0.);
	cairo_rectangle(cr, 0, 0, cw, ch);
	cairo_fill(cr);
	cairo_stroke(cr);

//draw the video
	if (priv->pixbuf != NULL) {
		cairo_save(cr);
		w = gdk_pixbuf_get_width(priv->pixbuf);
		h = gdk_pixbuf_get_height(priv->pixbuf);
		cairo_translate(cr, cw / 2., ch / 2.);
		radio = (gfloat) cw / w;
		if (((gfloat) ch / h) < radio)
			radio = (gfloat) ch / h;
		cairo_scale(cr, radio, radio);
		gdk_cairo_set_source_pixbuf(cr, priv->pixbuf, -0.5 * w, -0.5 * h);
		cairo_paint(cr);
		cairo_restore(cr);
	}
//draw the subtitle
	list = NULL;
	unlist = NULL;
	my_trace_bar_get_active_object(priv->trace_bar, &list, &unlist);
	if (list->data != NULL) {
		n_subtitle = g_list_length(list) - 1;
		cairo_set_line_width(cr, 1.);
		gtk_color_chooser_get_rgba(priv->subtitle_font_stroke_color,
				&stroke_color);
		gtk_color_chooser_get_rgba(priv->subtitle_font_fill_color, &fill_color);

		cairo_set_line_width(cr, 1.);
		//split the subtitle by </br> and see how many rows to draw at all.
		while (n_subtitle > 0) {
			rows = 0;
			data = g_hash_table_lookup(priv->subtitle_table, list->data);
			pbr = data->subtitle;
			while (1) {
				br = g_strstr_len(pbr, -1, "</br>");
				if (br == NULL)
					break;
				rows++;
				list_row = g_list_append(list_row, g_strndup(pbr, br - pbr));
				pbr = br + 5;
			}
			list_row = g_list_append(list_row, g_strdup(pbr));
			list = list->next;
			n_subtitle--;
		}
		n_subtitle = g_list_length(list_row);
		list_row = g_list_first(list_row);

		//draw all subtitles
		while (n_subtitle > 0) {
			text_layout = my_subtitle_parse_srt_text_line(cr, &fill_color,
					gtk_font_chooser_get_font_family(priv->subtitle_font),
					gtk_font_chooser_get_font_size(priv->subtitle_font),
					list_row->data);
			pango_layout_get_pixel_size(text_layout, &text_width, &text_height);
			cairo_save(cr);
			text_x = (cw - text_width) / 2.0;
			text_y = (gdouble) ch - n_subtitle * text_height;
			cairo_move_to(cr, text_x, text_y);
			pango_cairo_update_layout(cr, text_layout);
			pango_cairo_show_layout(cr, text_layout);
			pango_cairo_show_layout(cr, text_layout);
			cairo_move_to(cr, text_x, text_y);
			pango_cairo_update_layout(cr, text_layout);
			cairo_set_source_rgba(cr, stroke_color.red, stroke_color.green,
					stroke_color.blue, stroke_color.alpha);
			pango_cairo_layout_path(cr, text_layout);
			cairo_stroke(cr);
			g_object_unref(text_layout);
			cairo_restore(cr);
			//ready for next subtitle row.
			if (list_row->next != NULL)
				list_row = list_row->next;
			else
				break;
			n_subtitle--;
		}
		g_list_free_full(list_row, g_free);
	}
	g_list_free(unlist);
	g_list_free(list);

	GstQuery *duration = gst_query_new_duration(GST_FORMAT_TIME);
	GstQuery *position = gst_query_new_position(GST_FORMAT_TIME);
	GstBus *bus = gst_pipeline_get_bus(priv->pipeline);
	if (gst_element_query(priv->pipeline, duration)) {
		gst_query_parse_duration(duration, NULL, &dur);
	}
	if (gst_element_query(priv->pipeline, position)) {
		gst_query_parse_position(position, NULL, &pos);
	};
	gtk_range_set_range(priv->video_progress, 0, dur / 1000000);
	gtk_range_set_value(priv->video_progress, pos / 1000000);
	g_object_set(priv->trace_bar, "max", dur / 1000000000., "min", 0., "value",
			pos / 1000000000., NULL);
	gst_query_unref(duration);
	gst_query_unref(position);
	g_object_unref(bus);
	return TRUE;
}

void gst_bus_message_cb(GstBus *bus, GstMessage *message, MyMainWin *self) {
	guint i;
	gchar *temp;
	cairo_t *cr;
	cairo_surface_t *surf;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GstStructure *s = gst_message_get_structure(message);
	if (s != NULL && gst_structure_has_field(s, "pixbuf")) {
		if (priv->pixbuf != NULL) {
			g_object_unref(priv->pixbuf);
			priv->pixbuf = NULL;
		}
		gst_structure_get(s, "pixbuf", GDK_TYPE_PIXBUF, &priv->pixbuf, NULL);

		if (priv->pixbuf != NULL
				&& gtk_toggle_button_get_active(priv->mul_photo)) {
			temp = my_main_win_photo_name_generate(self,
					GST_MESSAGE_TIMESTAMP(message));
			gpointer *data = malloc(4 * sizeof(gpointer));
			data[0] = g_object_ref(priv->pixbuf);
			data[1] = temp;
			data[2] = GINT_TO_POINTER(gdk_pixbuf_get_width(priv->pixbuf));
			data[3] = GINT_TO_POINTER(gdk_pixbuf_get_height(priv->pixbuf));
			g_thread_pool_push(priv->take_photo_thread, data, NULL);
			my_main_win_info_bar_show_info(self, 2, "Photo is Saved as %s",
					temp);
		}
		gtk_widget_queue_draw(priv->content);
	}
}

static void *special_char_table[][12] = { { "General", 0x0021, 0x007f, 0x2600,
		0x26FF, NULL }, { "Punctuation & Unit", 0x3000, 0x303F, 0x3200, 0x32FF,
		0x3300, 0x33FF, NULL }, { "Arrow", 0x2190, 0x21ff, 0x27f0, 0x27ff,
		0x2900, 0x297f, NULL }, { "Math", 0x00D7, 0x00D7, 0x00F7, 0x00F7,
		0x2200, 0x22ff, 0x27c0, 0x27EF, 0x2980, 0x29ff, NULL },			//
		{ "Music", 0x1D000, 0x1D0FF, 0x1D200, 0x1D24F, NULL }, { "Currency",
				0x00A2, 0x00A5, 0x20a0, 0x20cf, NULL }, { "Number", 0x2460,
				0x24FF, NULL }, { "PinYin", 0x00A0, 0x00FF, 0x0100, 0x017F,
				0x0180, 0x024F, NULL },	//0x3100,0x312F,0x31A0,0x31BF,NULL},
		{ "Chinese Stroke", 0x31C0, 0x31EF, NULL }, { "YiJing", 0x4DC0, 0x4DFF,
		NULL }, { "Japan Katakana", 0x3040, 0x309F, 0x30A0, 0x30FF, NULL }, {
				"Greece", 0x10140, 0x1018F, 0x0370, 0x03FF, NULL },
		NULL, };

void char_stack_init(MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GtkGrid *grid;
	GtkScrolledWindow *scrolled;
	GtkButton *button;
	guint i = 0, j, k, x, y;
	gunichar *unicode;
	gchar *group_name, temp[10];
	GtkStyleContext *css;
	GtkStyleProvider *css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_data(css_provider,
			"button:hover:active,button:hover{background-color:#73D216;border-radius:5px;}\0",
			-1, NULL);
	while (special_char_table[i] != NULL) {
		group_name = special_char_table[i][0];
		j = 1;
		scrolled = gtk_scrolled_window_new(NULL, NULL);
		grid = gtk_grid_new();
		gtk_container_add(scrolled, grid);
		gtk_stack_add_titled(priv->char_stack, scrolled, group_name,
				group_name);
		x = 0, y = 0;
		while ((gchar*) special_char_table[i][j] != NULL) {
			for (k = (guint) special_char_table[i][j];
					k <= (guint) special_char_table[i][j + 1]; k++) {
				unicode = &k;
				memset(temp, 0, 10);
				g_unichar_to_utf8(*unicode, temp);
				button = gtk_button_new_with_label(temp);
				gtk_button_set_relief(button, GTK_RELIEF_NONE);
				css = gtk_widget_get_style_context(button);
				gtk_style_context_add_provider(css, css_provider, G_MAXUINT);
				g_signal_connect(button, "clicked",
						subtitle_add_special_char_cb, self);
				gtk_grid_attach(grid, button, x * 24, y * 24, 24, 24);
				x++;
				if (x >= 8) {
					y++;
					x = 0;
				}
			}
			j += 2;
		}
		//g_print("\n");
		i++;
		if (i > 11)
			break;
		gtk_widget_show_all(priv->char_stack);
	}
}

static void my_main_win_class_init(MyMainWinClass *klass) {
	gtk_widget_class_set_template_from_resource(klass, "/org/MainWin.glade");
	gtk_widget_class_bind_template_callback(klass, my_main_win__new);
	gtk_widget_class_bind_template_callback(klass, my_main_win_open);
	gtk_widget_class_bind_template_callback(klass, my_main_win_save);
	gtk_widget_class_bind_template_callback(klass, my_main_win_save_as);
	gtk_widget_class_bind_template_callback(klass, content_draw_cb);
	gtk_widget_class_bind_template_callback(klass, my_main_win_prev_cb);
	gtk_widget_class_bind_template_callback(klass, my_main_win_play_cb);
	gtk_widget_class_bind_template_callback(klass, my_main_win_pause_cb);
	gtk_widget_class_bind_template_callback(klass, my_main_win_next_cb);
	gtk_widget_class_bind_template_callback(klass,
			video_progress_change_value_cb);
	gtk_widget_class_bind_template_callback(klass, volume_changed_cb);
	gtk_widget_class_bind_template_callback(klass, my_main_win_take_photo_cb);
	gtk_widget_class_bind_template_callback(klass, add_subtitle_cb);
	gtk_widget_class_bind_template_callback(klass, pop_menu_del_cb);
	gtk_widget_class_bind_template_callback(klass, pop_menu_color_color_set_cb);
	gtk_widget_class_bind_template_callback(klass,
			pop_menu_subtitle_activate_cb);
	gtk_widget_class_bind_template_callback(klass,
			pop_menu_end_change_value_cb);
	gtk_widget_class_bind_template_callback(klass, pop_menu_label_activate_cb);
	gtk_widget_class_bind_template_callback(klass,
			pop_menu_start_change_value_cb);
	gtk_widget_class_bind_template_callback(klass, ex_popover_popup_down_cb);
	gtk_widget_class_bind_template_callback(klass, subtitle_add_br_cb);
	gtk_widget_class_bind_template_callback(klass, subtitle_bold_cb);
	gtk_widget_class_bind_template_callback(klass, subtitle_color_set_cb);
	gtk_widget_class_bind_template_callback(klass, subtitle_italic_cb);
	gtk_widget_class_bind_template_callback(klass, subtitle_under_line_cb);
	gtk_widget_class_bind_template_callback(klass, subtitle_auto_pause);
	gtk_widget_class_bind_template_callback(klass, subtitle_list_set_active);
	gtk_widget_class_bind_template_callback(klass, subtitle_list_set_start);
	gtk_widget_class_bind_template_callback(klass, subtitle_list_set_end);
	gtk_widget_class_bind_template_callback(klass, subtitle_list_set_text);
	gtk_widget_class_bind_template_callback(klass,
			pop_label_preview_draw_callback);
	gtk_widget_class_bind_template_callback(klass, subtitle_list_popup_down_cb);
	gtk_widget_class_bind_template_callback(klass, subtitle_list_save_cb);
	gtk_widget_class_bind_template_callback(klass, subtitle_list_open_cb);
	gtk_widget_class_bind_template_callback(klass, subtitle_list_edit_cb);
	gtk_widget_class_bind_template_callback(klass, subtitle_list_del_cb);
	gtk_widget_class_bind_template_callback(klass, subtitle_list_find_next_cb);
	gtk_widget_class_bind_template_callback(klass,
			subtitle_list_find_before_cb);
	gtk_widget_class_bind_template_callback(klass, subtitle_list_selection_cb);
	gtk_widget_class_bind_template_callback(klass,
			content_button_press_event_cb);
	gtk_widget_class_bind_template_callback(klass,subtitle_edit);
	gtk_widget_class_bind_template_callback(klass,	my_main_win_video_dir_album);

	gtk_widget_class_bind_template_child_private(klass, MyMainWin, content);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			video_progress);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			subtitle_trace);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin, info_bar);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			info_message);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin, mul_photo);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			photo_save_as_video_dir);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			photo_save_as_special_dir);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin, pop_menu);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			default_subtitle_last_time);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			subtitle_last_time);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin, subtitle);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			pop_menu_start);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			pop_menu_end);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			pop_menu_subtitle);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			pop_menu_label);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			subtitle_color);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			subtitle_font);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			subtitle_font_fill_color);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			subtitle_font_stroke_color);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			pop_menu_color);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin, pop_label);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			pop_label_text);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin, ex_popover);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin, ex_menu);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			pop_menu_ex_menu);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin, char_stack);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin, auto_pause);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			subtitle_list);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			subtitle_treeview);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			pop_label_preview);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			pop_subtitle_list);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			subtitle_list_edit);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			subtitle_list_edit_dialog);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			subtitle_list_edit_pattern);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			subtitle_list_edit_format);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			subtitle_list_edit_preview);
	gtk_widget_class_bind_template_child_private(klass, MyMainWin,
			find_entry);

}
;

static void my_main_win_init(MyMainWin *self) {
	MyMainWinClass *klass = MY_MAIN_WIN_GET_CLASS(self);
	gtk_widget_init_template(self);
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	priv->subtitle_table = g_hash_table_new_full(g_direct_hash, g_direct_equal,
	NULL, NULL);
	priv->src = gst_element_factory_make("playbin", "src");
	priv->videosink = gst_element_factory_make("gdkpixbufsink",
			"gdkpixbufsink");
	priv->audiosink = gst_element_factory_make("autoaudiosink", "audiosink");
	priv->pipeline = gst_pipeline_new("line");
	priv->pixbuf = NULL;
	priv->cur_state = GST_STATE_PAUSED;
	priv->subtitle_index = 1;
	priv->active_subtitle = NULL;
	gst_bin_add_many(priv->pipeline, priv->src, NULL);
	g_object_set(priv->src, "video-sink", priv->videosink, "audio-sink",
			priv->audiosink, NULL);
	GstBus *bus = gst_pipeline_get_bus(priv->pipeline);
	g_signal_connect(bus, "message", gst_bus_message_cb, self);
	gst_bus_add_signal_watch(bus);

	priv->take_photo_thread = g_thread_pool_new(my_main_win_take_photo_thread,
	NULL, 16, FALSE, NULL);

	priv->trace_bar = my_trace_bar_new("Sub Title");
	//gtk_box_pack_start(priv->subtitle_trace, priv->trace_bar, TRUE, FALSE, 0);
	gtk_container_add(priv->subtitle_trace, priv->trace_bar);
	gtk_spin_button_set_value(priv->subtitle_last_time,
			gtk_spin_button_get_value(priv->default_subtitle_last_time));
	g_signal_connect(priv->trace_bar, "obj_selected",
			my_main_win_trace_bar_obj_selected, self);
	g_signal_connect(priv->trace_bar, "obj_unselected",
			my_main_win_trace_bar_obj_unselected, self);
	g_signal_connect(priv->trace_bar, "obj_preselected",
			my_main_win_trace_bar_obj_preselected, self);
	g_signal_connect(priv->trace_bar, "obj_unpreselected",
			my_main_win_trace_bar_obj_unpreselected, self);
	g_signal_connect(priv->trace_bar, "obj_range_change",
			my_main_win_trace_bar_obj_range_change, self);
	char_stack_init(self);
	priv->markup = g_regex_new("<[^>]+>", G_REGEX_OPTIMIZE, 0, NULL);
	gtk_widget_set_sensitive(priv->subtitle_list_edit, FALSE);
	gtk_entry_set_text(priv->subtitle_list_edit_pattern,".+");
	gtk_entry_set_text(priv->subtitle_list_edit_format,"%p");
	priv->videoalbum=my_video_album_new();
}
;

MyMainWin* my_main_win_new(gchar *title, gchar *uri, gboolean play) {
	MyMainWin *m = g_object_new(MY_TYPE_MAIN_WIN, NULL);
	MyMainWinPrivate *priv = my_main_win_get_instance_private(m);
	GstStateChangeReturn state;
	if (title != NULL)
		gtk_window_set_title(m, title);
	if (uri != NULL)
		g_object_set(priv->src, "uri", uri, NULL);
	if (play) {
		state = gst_element_set_state(priv->pipeline, GST_STATE_PLAYING);
		g_print("state:%02x\n", state);
		priv->cur_state = GST_STATE_PLAYING;
	}
//my_main_win_info_bar_show_info(m, 3, "Good Morning");
	return m;
}
;

