/*
 * MainWin.c
 *
 *  Created on: 2019年11月21日
 *      Author: tom
 */

#include "../ui/MainWin.h"

#include "../ui/gresource.h"
typedef struct {
	GstElement *src, *video_convert, *audio_convert, *videosink, *audiosink,
			*volume;
	GstPipeline *pipeline;
	GHashTable *subtitle_table;
	GtkDrawingArea *content;
	GdkPixbuf *pixbuf;
	GtkScale *video_progress;
	GstState cur_state;
	GtkBox *subtitle_trace;
	MyTraceBar *trace_bar;
	GtkInfoBar *info_bar;
	GtkLabel *info_message;
	guint info_timeout;
	GtkToggleButton *mul_photo;
	GtkCheckButton *photo_save_as_video_dir;
	GtkFileChooserButton *photo_save_as_special_dir;
	GtkSpinButton *default_subtitle_last_time, *subtitle_last_time;
	GtkEntry *subtitle;
	GtkPopoverMenu *pop_menu;
	GtkSpinButton *pop_menu_start, *pop_menu_end;
	GtkEntry *pop_menu_subtitle, *pop_menu_label;
	GtkColorButton *subtitle_color, *subtitle_font_fill_color,
			*subtitle_font_stroke_color, *pop_menu_color;
	guint64 subtitle_index;
	GList *active_subtitle;
	GtkFontButton *subtitle_font;
	gpointer *selected_obj;
	GtkPopover *pop_label, *ex_popover;
	GtkLabel *pop_label_text;
	GtkButton *pop_menu_ex_menu, *ex_menu;
	GtkStack *char_stack;
	GRegex *markup;
} MyMainWinPrivate;

typedef struct {
	SubtitleFormat format;
	GdkRGBA color;
	gchar *text;
} SubtitleDescribe;

void subtitle_describe_free(SubtitleDescribe *des) {
	g_free(des->text);
	g_free(des);
}
SubtitleDescribe* subtitle_describe_new(GdkRGBA *color, SubtitleFormat format,
		gchar *text) {
	SubtitleDescribe *des = calloc(1, sizeof(SubtitleDescribe));
	des->format = format;
	if (color != NULL) {
		des->color.alpha = color->alpha;
		des->color.blue = color->blue;
		des->color.green = color->green;
		des->color.red = color->red;
	}
	des->text = g_strdup(text);
	return des;
}
SubtitleDescribe* subtitle_describe_copy_format(SubtitleDescribe *des) {
	SubtitleDescribe *des_copy = calloc(1, sizeof(SubtitleDescribe));
	des_copy->format = des->format;
	des_copy->color.alpha = des->color.alpha;
	des_copy->color.blue = des->color.blue;
	des_copy->color.green = des->color.green;
	des_copy->color.red = des->color.red;
	des_copy->text = NULL;
	return des_copy;
}

G_DEFINE_TYPE_WITH_CODE(MyMainWin, my_main_win, GTK_TYPE_WINDOW,
		G_ADD_PRIVATE(MyMainWin));

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
			gst_element_set_state(priv->pipeline, GST_STATE_NULL);
			gst_element_set_state(priv->pipeline, GST_STATE_PLAYING);
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
	g_object_set(priv->volume, "volume", value / 100., NULL);
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

	g_object_get(priv->src, "uri", &temp, NULL);
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

void add_subtitle_cb(GtkButton *button, MyMainWin *self) {
	gchar *subtitle, *describe;
	gdouble current_pos, last_time;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GdkRGBA color;
	subtitle = g_strdup(gtk_entry_get_text(priv->subtitle));
	gtk_entry_set_text(priv->subtitle, "\0");
	current_pos = my_trace_bar_get_value(priv->trace_bar);
	last_time = gtk_spin_button_get_value(priv->subtitle_last_time);
	gtk_spin_button_set_value(priv->subtitle_last_time,
			gtk_spin_button_get_value(priv->default_subtitle_last_time));
	gtk_color_chooser_get_rgba(priv->subtitle_color, &color);
	describe = g_strdup_printf("%d", priv->subtitle_index);
	my_trace_bar_add_obj_range(priv->trace_bar, subtitle, current_pos,
			current_pos + last_time, describe, &color);
	g_hash_table_insert(priv->subtitle_table,
			GINT_TO_POINTER(priv->subtitle_index), subtitle);
	priv->subtitle_index++;
	g_free(describe);

}

void pop_menu_del_cb(GtkButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	my_trace_bar_del_obj_range(priv->trace_bar, priv->selected_obj);
	g_free(priv->selected_obj);
	priv->selected_obj = NULL;
	gtk_popover_popdown(priv->pop_menu);
}

void pop_menu_color_color_set_cb(GtkColorButton *widget, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GdkRGBA color;
	gtk_color_chooser_get_rgba(priv->pop_menu_color, &color);
	my_trace_bar_set_obj_color(priv->trace_bar, priv->selected_obj, &color);
}

void pop_menu_subtitle_activate_cb(GtkEntry *entry, MyMainWin *self) {
	g_print("changed subtitle");

}

void pop_menu_end_change_value_cb(GtkSpinButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gdouble end, start;
	my_trace_bar_get_obj_range(priv->trace_bar, priv->selected_obj, &start,
			&end);
	end = gtk_spin_button_get_value(priv->pop_menu_end);
	my_trace_bar_set_obj_range(priv->trace_bar, priv->selected_obj, start, end);
}

void pop_menu_label_activate_cb(GtkEntry *entry, MyMainWin *self) {
	gchar *text;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	text = gtk_entry_get_text(priv->pop_menu_label);
	my_trace_bar_set_obj_describe(priv->trace_bar, priv->selected_obj, text);
}

void pop_menu_start_change_value_cb(GtkSpinButton *button, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gdouble end, start;
	my_trace_bar_get_obj_range(priv->trace_bar, priv->selected_obj, &start,
			&end);
	start = gtk_spin_button_get_value(priv->pop_menu_start);
	my_trace_bar_set_obj_range(priv->trace_bar, priv->selected_obj, start, end);
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
	GdkRGBA color;
	gint s = 0, e = 0, len, ns, ne;
	guchar r, g, b;
	gchar *text;
	GString *temp = g_string_new("");
	GtkEntry *entry = gtk_popover_get_relative_to(priv->ex_popover);
	gtk_color_chooser_get_rgba(button, &color);
	g_object_get(entry, "cursor-position", &s, "selection-bound", &e, "text",
			&text, NULL);
	if (s > e) {
		len = s;
		s = e;
		e = len;
	}
	len = e - s;
	r = color.red * 255;
	g = color.green * 255;
	b = color.blue * 255;
	temp = g_string_append_len(temp, text, s);
	g_string_append_printf(temp, "<font color=\"#%02x%02x%02x\">", r, g, b);
	ns = temp->len;
	ne = ns + len;
	temp = g_string_append_len(temp, text + s, len);
	g_string_append_printf(temp, "</font>");
	temp = g_string_append(temp, text + e);
	gtk_entry_set_text(entry, temp->str);
	gtk_editable_select_region(entry, ns, ne);
	g_string_free(temp, TRUE);
	g_free(text);
}

void subtitle_bold_cb(GtkButton *button, MyMainWin *self) {
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
	g_string_append_printf(temp, "<b>");
	ns = temp->len;
	ne = ns + len;
	temp = g_string_append_len(temp, text + s, len);
	g_string_append_printf(temp, "</b>");
	temp = g_string_append(temp, text + e);
	gtk_entry_set_text(entry, temp->str);
	gtk_editable_select_region(entry, ns, ne);
	g_string_free(temp, TRUE);
	g_free(text);
}

void subtitle_italic_cb(GtkButton *button, MyMainWin *self) {
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
	g_string_append_printf(temp, "<i>");
	ns = temp->len;
	ne = ns + len;
	temp = g_string_append_len(temp, text + s, len);
	g_string_append_printf(temp, "</i>");
	temp = g_string_append(temp, text + e);
	gtk_entry_set_text(entry, temp->str);
	gtk_editable_select_region(entry, ns, ne);
	g_string_free(temp, TRUE);
	g_free(text);
}

void subtitle_under_line_cb(GtkButton *button, MyMainWin *self) {
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
	g_string_append_printf(temp, "<u>");
	ns = temp->len;
	ne = ns + len;
	temp = g_string_append_len(temp, text + s, len);
	g_string_append_printf(temp, "</u>");
	temp = g_string_append(temp, text + e);
	gtk_entry_set_text(entry, temp->str);
	gtk_editable_select_region(entry, ns, ne);
	g_string_free(temp, TRUE);
	g_free(text);
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

void my_main_win_trace_bar_obj_selected(MyTraceBar *bar, gpointer obj,
		GdkRectangle *rectangle, MyMainWin *self) {
	gdouble s, e;
	GdkRGBA *color;
	gchar *describe;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	my_trace_bar_get_obj_range(priv->trace_bar, obj, &s, &e);
	color = my_trace_bar_get_obj_color(priv->trace_bar, obj);
	describe = my_trace_bar_get_obj_describe(priv->trace_bar, obj);
	priv->selected_obj = obj;
	gtk_popover_set_relative_to(priv->pop_menu, bar);
	gtk_spin_button_set_value(priv->pop_menu_start, s);
	gtk_spin_button_set_value(priv->pop_menu_end, e);
	gtk_entry_set_text(priv->pop_menu_subtitle, obj);
	gtk_entry_set_text(priv->pop_menu_label, describe);
	gtk_color_chooser_set_rgba(priv->pop_menu_color, color);
	gtk_popover_set_pointing_to(priv->pop_menu, rectangle);
	gtk_popover_popup(priv->pop_menu);

}

void my_main_win_trace_bar_obj_preselected(MyTraceBar *bar, gpointer obj,
		GdkRectangle *rectangle, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gtk_label_set_text(priv->pop_label_text, obj);
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
	priv->selected_obj = NULL;
}

void my_main_win_trace_bar_obj_active_cb(MyTraceBar *bar, gchar *subtitle,
		MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	priv->active_subtitle = g_list_append(priv->active_subtitle, subtitle);
}

void my_main_win_trace_bar_obj_range_change(MyTraceBar *bar, gpointer obj,
		gdouble start, gdouble end, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	if (priv->selected_obj != obj)
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
		0, 255 }, { "cyan", 0, 255, 255 }, { "white", 255, 255, 255 },
NULL, };

GList* subtitle_parse_markup(gchar *str, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gint s, e, p = 0, c;
	guint i;
	gchar *temp;
	GdkRGBA color;
	GMatchInfo *info;
	GList *ParseResult = NULL;
	SubtitleDescribe *des  = subtitle_describe_new(NULL,
			Subtitle_Format_None, NULL),*temp_des;
	GQueue *format_stack = g_queue_new();
	g_regex_match(priv->markup, str, 0, &info);
	while (g_match_info_matches(info)) {
		temp = g_match_info_fetch(info, 0);
		g_match_info_fetch_pos(info, 0, &s, &e);
		if (g_strstr_len(temp, -1, "i") != NULL) {
			if (g_strstr_len(temp, -1, "</") == NULL) {
				g_queue_push_tail(format_stack,
						subtitle_describe_copy_format(des));
				des->format |= Subtitle_Format_Itatic;
			} else {
				subtitle_describe_free(des);
				des = g_queue_pop_tail(format_stack);
			}
		}
		if (g_strstr_len(temp, -1, "b") != NULL) {
			if (g_strstr_len(temp, -1, "</") == NULL) {
				g_queue_push_tail(format_stack,
						subtitle_describe_copy_format(des));
				des->format |= Subtitle_Format_Bold;
			} else {
				subtitle_describe_free(des);
				des = g_queue_pop_tail(format_stack);
			}
		}
		if (g_strstr_len(temp, -1, "u") != NULL) {
			if (g_strstr_len(temp, -1, "</") == NULL) {
				g_queue_push_tail(format_stack,
						subtitle_describe_copy_format(des));
				des->format |= Subtitle_Format_Underline;
			} else {
				subtitle_describe_free(des);
				des = g_queue_pop_tail(format_stack);
			}
		}
		if (g_strstr_len(temp, -1, "font") != NULL
				&& g_strstr_len(temp, -1, "color=") != NULL) {
			if (g_strstr_len(temp, -1, "</") == NULL) {
				g_queue_push_tail(format_stack,
						subtitle_describe_copy_format(des));
				des->format |= Subtitle_Format_Special_Color;
				i = 0;
				while (subtitle_normal_color[i] != NULL) {
					if (g_strstr_len(temp, -1,
							subtitle_normal_color[i][0])!=NULL) {
						color.red = (guint)subtitle_normal_color[i][1];
						color.green = (guint)subtitle_normal_color[i][2];
						color.blue = (guint)subtitle_normal_color[i][3];
						break;
					}
					i++;
				}
				if (subtitle_normal_color[i] == NULL) {
					c = g_strstr_len(temp, -1, "#");
					sscanf(c + 1, "%02x,%02x,%02x", &color.red, &color.green,
							&color.blue);
				}
			} else {
				subtitle_describe_free(des);
				des = g_queue_pop_tail(format_stack);
			}
		}

		if (s - p != 0) {
			temp_des=subtitle_describe_copy_format(des);
			temp_des->text=g_strndup(str+p,s-p);
			ParseResult=g_list_append(ParseResult,temp_des);
		}
		p=e;
		g_print("get %s\n", temp);
		g_free(temp);
		g_match_info_next(info, NULL);
	}
	g_queue_free_full(format_stack,subtitle_describe_free);
	subtitle_describe_free(des);
	return g_list_first(ParseResult);
}

gboolean content_draw_cb(GtkDrawingArea *content, cairo_t *cr, MyMainWin *self) {
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	gint w, h, rows;
	gfloat radio;
	gint64 dur, pos;
	GList *list;
	gint text_height, text_width;
	GdkRGBA fill_color, stroke_color;
	gchar *font_des_string;
	PangoLayout *text_layout;
	PangoLayoutLine *text_line;
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
	if (priv->active_subtitle != NULL) {
		list = priv->active_subtitle;
		rows = g_list_length(priv->active_subtitle);
		text_height = (gdouble) 0.07 * ch;
		cairo_set_font_size(cr, text_height);
		cairo_set_line_width(cr, 1.);
		gtk_color_chooser_get_rgba(priv->subtitle_font_fill_color, &fill_color);
		gtk_color_chooser_get_rgba(priv->subtitle_font_stroke_color,
				&stroke_color);
		font_des_string = gtk_font_chooser_get_font(priv->subtitle_font);
		text_layout = pango_cairo_create_layout(cr);
		PangoFontDescription *desc = pango_font_description_from_string(
				font_des_string);
		pango_layout_set_font_description(text_layout, desc);
		pango_font_description_free(desc);
		cairo_set_line_width(cr, 1.);
		while (rows > 0) {
			subtitle_parse_markup(list->data, self);
			pango_layout_set_text(text_layout, list->data, -1);
			pango_layout_get_pixel_size(text_layout, &text_width, &text_height);
			cairo_move_to(cr, (cw - text_width) / 2.0,
					(gdouble) ch - rows * text_height * 1.1);
			cairo_set_source_rgba(cr, fill_color.red, fill_color.green,
					fill_color.blue, fill_color.alpha);
			pango_cairo_update_layout(cr, text_layout);
			pango_cairo_show_layout(cr, text_layout);
			//cairo_move_to(cr,(cw-text_width)/2.0,(gdouble)ch-rows*text_height*1.1);
			cairo_set_source_rgba(cr, stroke_color.red, stroke_color.green,
					stroke_color.blue, stroke_color.alpha);
			pango_cairo_layout_path(cr, text_layout);
			cairo_stroke(cr);
			//pango_cairo_update_layout(cr,text_layout);
			//text_line=pango_layout_get_line_readonly(text_layout,pango_layout_get_line_count(text_layout) - 1);
			//pango_cairo_show_layout_line(cr,text_line);
			rows--;
			list = list->next;
		}
		g_object_unref(text_layout);
		g_free(font_des_string);
		g_list_free(priv->active_subtitle);
		priv->active_subtitle = NULL;
	}

	GstQuery *duration = gst_query_new_duration(GST_FORMAT_TIME);
	GstQuery *position = gst_query_new_position(GST_FORMAT_TIME);
	GstBus *bus = gst_pipeline_get_bus(priv->pipeline);
	if (gst_element_query(priv->pipeline, duration)) {
		gst_query_parse_duration(duration, NULL, &dur);
	}
	if (gst_element_query(priv->pipeline, position)) {
		gst_query_parse_position(position, NULL, &pos);
	};
	//g_object_set(priv->progress,"lower",0,"upper",dur/1000000,"value",pos/1000000,NULL);
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
			gdk_pixbuf_unref(priv->pixbuf);
		}
		gst_structure_get(s, "pixbuf", GDK_TYPE_PIXBUF, &priv->pixbuf, NULL);

		if (gtk_toggle_button_get_active(priv->mul_photo)) {
			temp = my_main_win_photo_name_generate(self,
					GST_MESSAGE_TIMESTAMP(message));
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
				g_sprintf(temp, "%lc", *unicode);
				//g_print("%lc", *unicode);
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

void gst_src_new_pad(GstElement *object, GstPad *pad, MyMainWin *self) {
	guint i, j;
	GstStructure *s;
	GstPad *sinkpad = NULL, *srcpad = NULL;
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	GstCaps *cap = gst_pad_get_current_caps(pad);
	i = gst_caps_get_size(cap);
	g_print("get new pad size:%d\n", i);
	for (j = 0; j < i; j++) {
		s = gst_caps_get_structure(cap, j);
		g_print("%2d:\"%s\"\n", j, gst_structure_get_name(s));

		if (g_strstr_len(gst_structure_get_name(s), -1, "video/x-raw") != NULL) {
//			gst_bin_add_many(priv->pipeline,priv->video_convert,priv->videosink,NULL);
//			sinkpad = gst_element_get_static_pad(priv->videosink, "sink");
//			srcpad = gst_element_get_static_pad(priv->video_convert, "src");
//			gst_pad_link(srcpad, sinkpad);
//			g_object_unref(sinkpad);
//			g_object_unref(srcpad);

			sinkpad = gst_element_get_static_pad(priv->video_convert, "sink");
			gst_pad_link(pad, sinkpad);
		};

		if (g_strstr_len(gst_structure_get_name(s), -1, "audio/x-raw") != NULL) {
//			gst_bin_add_many(priv->pipeline,priv->audio_convert,priv->audiosink,priv->volume,NULL);
//			sinkpad = gst_element_get_static_pad(priv->volume, "sink");
//			srcpad = gst_element_get_static_pad(priv->audio_convert, "src");
//			gst_pad_link(srcpad, sinkpad);
//			g_object_unref(sinkpad);
//			g_object_unref(srcpad);
//
//			sinkpad = gst_element_get_static_pad(priv->audiosink, "sink");
//			srcpad = gst_element_get_static_pad(priv->volume, "src");
//			gst_pad_link(srcpad, sinkpad);
//			g_object_unref(sinkpad);
//			g_object_unref(srcpad);

			sinkpad = gst_element_get_static_pad(priv->audio_convert, "sink");
			gst_pad_link(pad, sinkpad);
		};
	}
	gst_caps_unref(cap);
	if (sinkpad != NULL)
		gst_object_unref(sinkpad);
}
;

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

}
;

static void my_main_win_init(MyMainWin *self) {
	MyMainWinClass *klass = MY_MAIN_WIN_GET_CLASS(self);
	gtk_widget_init_template(self);
	MyMainWinPrivate *priv = my_main_win_get_instance_private(self);
	priv->subtitle_table = g_hash_table_new_full(g_direct_hash, g_direct_equal,
	NULL, g_free);
	priv->src = gst_element_factory_make("uridecodebin", "src");
	priv->video_convert = gst_element_factory_make("autovideoconvert",
			"video_convert");
	priv->audio_convert = gst_element_factory_make("audioconvert",
			"audio_convert");
	priv->videosink = gst_element_factory_make("gdkpixbufsink",
			"gdkpixbufsink");
	priv->volume = gst_element_factory_make("volume", "volume");
	priv->audiosink = gst_element_factory_make("autoaudiosink", "audiosink");
	priv->pipeline = gst_pipeline_new("line");
	priv->pixbuf = NULL;
	priv->cur_state = GST_STATE_PAUSED;
	priv->subtitle_index = 0;
	priv->active_subtitle = NULL;
	/*									--audio_convert--audiosink
	 * Create gstreamer pipeline src
	 *									--video_convert--videosink
	 */
	gst_bin_add_many(priv->pipeline, priv->src, priv->audio_convert,
			priv->video_convert, priv->videosink, priv->audiosink, priv->volume,
			NULL);
	GstPad *sink = gst_element_get_static_pad(priv->videosink, "sink");
	GstPad *src = gst_element_get_static_pad(priv->video_convert, "src");
	gst_pad_link(src, sink);
	g_object_unref(sink);
	g_object_unref(src);

	sink = gst_element_get_static_pad(priv->volume, "sink");
	src = gst_element_get_static_pad(priv->audio_convert, "src");
	gst_pad_link(src, sink);
	g_object_unref(sink);
	g_object_unref(src);

	sink = gst_element_get_static_pad(priv->audiosink, "sink");
	src = gst_element_get_static_pad(priv->volume, "src");
	gst_pad_link(src, sink);
	g_object_unref(sink);
	g_object_unref(src);

	GstBus *bus = gst_pipeline_get_bus(priv->pipeline);
	g_signal_connect(bus, "message", gst_bus_message_cb, self);
	gst_bus_add_signal_watch(bus);
	g_signal_connect(priv->src, "pad-added", gst_src_new_pad, self);
	priv->trace_bar = my_trace_bar_new("Sub Title");
	gtk_box_pack_start(priv->subtitle_trace, priv->trace_bar, TRUE, FALSE, 0);
	gtk_spin_button_set_value(priv->subtitle_last_time,
			gtk_spin_button_get_value(priv->default_subtitle_last_time));
	g_signal_connect(priv->trace_bar, "obj_active",
			my_main_win_trace_bar_obj_active_cb, self);
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

