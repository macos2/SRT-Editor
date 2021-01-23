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
	gdouble start, end;
} SRTSubtitleData;

typedef struct {
	GTree *tree;
	guint64 count;
	GRegex *hh_mm_ss_sss;
} MySrtSubtitlePrivate;
static void my_srt_subtitle_subtitle_iface_init(MySubtitleInterface *iface);
void my_srt_subtitle_del_subtitle(MySrtSubtitle *self, guint64 index);
void my_srt_subtitle_to_file(MySrtSubtitle *self, gchar *location);
gchar* my_srt_subtitle_to_string(MySrtSubtitle *self);
void my_srt_subtitle_load_file(MySrtSubtitle *self, gchar *location);
gchar* my_srt_subtitle_get_subtitle(MySrtSubtitle *self, guint64 index,
		gdouble *start, gdouble *end, va_list ap);
guint64 my_srt_subtitle_get_total_size(MySrtSubtitle *self);

guint64 my_srt_subtitle_add_subtitle(MySrtSubtitle *self, gchar *text,
		gdouble start, gdouble end, va_list ap);
G_DEFINE_TYPE_WITH_CODE(MySrtSubtitle, my_srt_subtitle, G_TYPE_OBJECT,
		G_ADD_PRIVATE(MySrtSubtitle) G_IMPLEMENT_INTERFACE(MY_TYPE_SUBTITLE,my_srt_subtitle_subtitle_iface_init))

SRTSubtitleData* srt_subtitle_data_new(gchar *subtitle, gchar *font,
		GdkRGBA *color, gdouble start, gdouble end) {
	SRTSubtitleData *data = g_malloc(sizeof(SRTSubtitleData));
	data->font = g_strdup(font);
	data->subtitle = g_strdup(subtitle);
	data->start = start;
	data->end = end;
	if (color != NULL) {
		data->color.alpha = color->alpha;
		data->color.blue = color->blue;
		data->color.green = color->green;
		data->color.red = color->red;
	}
	return data;
}

gint srt_subtitle_data_compare(SRTSubtitleData *a, SRTSubtitleData *b,
		gpointer user_data) {
	if (a->start > b->start)
		return -1;
	return 1;
}

void srt_subtitle_data_free(SRTSubtitleData *data) {
	g_free(data->font);
	g_free(data->subtitle);
	g_free(data);
}

void my_srt_subtitle_dispose(MySrtSubtitle *self) {

}
;

void my_srt_subtitle_finalize(MySrtSubtitle *self) {
	MySrtSubtitlePrivate *priv = my_srt_subtitle_get_instance_private(self);
	g_tree_destroy(priv->tree);
	g_regex_unref(priv->hh_mm_ss_sss);
}
;

static void my_srt_subtitle_subtitle_iface_init(MySubtitleInterface *iface) {
	iface->add_subtitle = my_srt_subtitle_add_subtitle;
	iface->del_subtitle = my_srt_subtitle_del_subtitle;
	iface->to_file = my_srt_subtitle_to_file;
	iface->to_string = my_srt_subtitle_to_string;
	iface->load_file = my_srt_subtitle_load_file;
	iface->get_subtitle = my_srt_subtitle_get_subtitle;
	iface->get_total_size = my_srt_subtitle_get_total_size;
}

static void my_srt_subtitle_class_init(MySrtSubtitleClass *klass) {
	GObjectClass *obj_class = klass;
	obj_class->finalize = my_srt_subtitle_finalize;
}

static void my_srt_subtitle_init(MySrtSubtitle *self) {
	MySrtSubtitlePrivate *priv = my_srt_subtitle_get_instance_private(self);
	priv->tree = g_tree_new_full(srt_subtitle_data_compare, NULL, NULL,
			srt_subtitle_data_free);
	priv->count = 0;
	priv->hh_mm_ss_sss = g_regex_new("\d\d:\d\d:\d\d\.\d\d\d", G_REGEX_OPTIMIZE,
			0, NULL);
}

guint64 my_srt_subtitle_add_subtitle(MySrtSubtitle *self, gchar *text,
		gdouble start, gdouble end, va_list ap) {
	GdkRGBA *color = NULL;
	gchar *font = NULL;
	gint format;
	MySrtSubtitlePrivate *priv = my_srt_subtitle_get_instance_private(self);
	do {
		format = va_arg(ap, gint);
		if (format == -1 || format == 0)
			break;
		if (format == Subtitle_Format_Special_Color)
			color = va_arg(ap, GdkRGBA*);
		if (format == Subtitle_Format_Special_Font)
			font = va_arg(ap, gchar*);
	} while (1);
	SRTSubtitleData *data = srt_subtitle_data_new(text, font, color, start,
			end);
	g_tree_insert(priv->tree, GINT_TO_POINTER(priv->count), data);
	priv->count++;
	return priv->count - 1;
}

void my_srt_subtitle_del_subtitle(MySrtSubtitle *self, guint64 index) {
	MySrtSubtitlePrivate *priv = my_srt_subtitle_get_instance_private(self);
	g_tree_remove(priv->tree, GINT_TO_POINTER(index));
}

void my_srt_subtitle_to_file(MySrtSubtitle *self, gchar *location) {
	gchar *contents;
	if (g_access(location, F_OK) == 0)
		g_unlink(location);
	contents = my_srt_subtitle_to_string(self);
	g_file_set_contents(location, contents, -1, NULL);
	g_free(contents);
}

guint64 to_string_index;
void my_srt_subtitle_data_to_string(gpointer key, SRTSubtitleData *data,
		GString *string) {
	guint hour, minute;
	gdouble second;
	g_string_append_printf(string, "%d\n", to_string_index);
	to_string_index++;
	time_to_hh_mm_ss_sss(data->start, &hour, &minute, &second);
	g_string_append_printf(string, "%02d:%02d:%0.3lf --> ", hour, minute,
			second);
	time_to_hh_mm_ss_sss(data->end, &hour, &minute, &second);
	g_string_append_printf(string, "%02d:%02d:%0.3lf\n%s\n\n", hour, minute,
			second, data->subtitle);
}

gchar* my_srt_subtitle_to_string(MySrtSubtitle *self) {
	MySrtSubtitlePrivate *priv = my_srt_subtitle_get_instance_private(self);
	GString *string = g_string_new("");
	to_string_index = 0;
	gchar *result;
	g_tree_foreach(priv->tree, my_srt_subtitle_data_to_string, string);
	result = string->str;
	g_string_free(string, FALSE);
	return result;
}

void my_srt_subtitle_load_file(MySrtSubtitle *self, gchar *location) {
	if (g_access(location, R_OK) == -1)
		return;
	MySrtSubtitlePrivate *priv = my_srt_subtitle_get_instance_private(self);
	gsize len;
	guint64 index;
	GError *err = NULL;
	GFile *file = g_file_new_for_path(location);
	gchar *line = NULL, **strv;
	GString *subtitle = NULL;
	gchar *start_s, *end_s;
	gdouble start, end;
	GFileInputStream *input = g_file_read(file, NULL, &err);
	GDataInputStream *data;
	GMatchInfo *info;
	if (err != NULL) {
		g_printerr("ERR:%s\n", err->message);
		g_error_free(err);
		g_object_unref(input);
		g_object_unref(file);
	}
	data = g_data_input_stream_new(input);

	do {
		// read index eg:"1"
		line = g_data_input_stream_read_line(data, &len, NULL, &err);
		if (err != NULL) {
			g_printerr("ERR:%s\n", err->message);
			g_free(line);
			break;
		}
		if (line == NULL) {
			//the end of the file
			break;
		}
		index = atol(line);
		g_free(line);

		//read the time eg: "12:34:56.789 --> 21:34:56.789"
		line = g_data_input_stream_read_line(data, &len, NULL, &err);
		g_regex_match(priv->hh_mm_ss_sss, line, 0, &info);
		start_s = g_match_info_fetch(info, 0);
		g_match_info_next(info, NULL);
		end_s = g_match_info_fetch(info, 0);
		g_match_info_free(info);
		g_free(line);
		//parse the start and end time
		strv = g_strsplit(start_s, ":", -1);
		start = g_strtod(strv[0], NULL) * 3600. + g_strtod(strv[1], NULL) * 60.
				+ g_strtod(strv[2], NULL);
		g_strfreev(strv);
		g_free(start_s);
		strv = g_strsplit(end_s, ":", -1);
		end = g_strtod(strv[0], NULL) * 3600. + g_strtod(strv[1], NULL) * 60.
				+ g_strtod(strv[2], NULL);
		g_strfreev(strv);
		g_free(end_s);

		//read subtitle context
		do {
			//read until to the blank line
			line = g_data_input_stream_read_line(data, &len, NULL, &err);
			if (g_strcmp0(line, "") == 0) {
				g_free(line);
				break;
			}
			if (subtitle == NULL)
				subtitle = g_string_new("");
			else
				subtitle = g_string_append(subtitle, "\n");
			subtitle = g_string_append(subtitle, line);
			g_free(line);
		} while (1);
		my_subtitle_add_subtitle(self, subtitle->str, start, end);
		g_string_free(subtitle, TRUE);
		subtitle = NULL;
	} while (1);
	g_object_unref(data);
	g_input_stream_close(input, NULL, NULL);
	g_object_unref(input);
	g_object_unref(file);
}

gchar* my_srt_subtitle_get_subtitle(MySrtSubtitle *self, guint64 index,
		gdouble *start, gdouble *end, va_list ap) {
	MySrtSubtitlePrivate *priv = my_srt_subtitle_get_instance_private(self);
	SRTSubtitleData *data;
	SubtitleFormat format;
	GdkRGBA *color;
	gchar *font;
	data = g_tree_lookup(priv->tree, GINT_TO_POINTER(index));
	if (data == NULL)
		return NULL;
	do {
		format = va_arg(ap, SubtitleFormat);
		if (format == Subtitle_Format_None)
			break;
		switch (format) {
		case Subtitle_Format_Special_Color:
			color = va_arg(ap, GdkRGBA*);
			color->alpha = data->color.alpha;
			color->blue = data->color.blue;
			color->green = data->color.green;
			color->red = data->color.red;
			break;
		case Subtitle_Format_Special_Font:
			font = va_arg(ap, gchar**);
			*font = data->font;
			break;
		default:
			break;
		}
	} while (1);
	return data->subtitle;
}

guint64 my_srt_subtitle_get_total_size(MySrtSubtitle *self) {
	MySrtSubtitlePrivate *priv = my_srt_subtitle_get_instance_private(self);
	return priv->count;
}

MySrtSubtitle* my_srt_subtitle_new() {
	MySrtSubtitle *sub = g_object_new(MY_TYPE_SRT_SUBTITLE, NULL);
	return sub;
}

PangoLayout* my_subtitle_parse_srt_text_line(cairo_t *cr, GdkRGBA *color,
		PangoFontFamily *font_family, gsize font_size, gchar *subtitle_text_line) {
	GRegex *start_markup = g_regex_new("<[^>]+>", G_REGEX_OPTIMIZE, 0, NULL);
	GMatchInfo *info;
	gchar *temp, *temp2, *temp3;
	GQueue *queue = g_queue_new();
	SubtitleFormat format = Subtitle_Format_None;
	gint r, g, b, s, e, len, p = 0;
	if (font_size < PANGO_SCALE)
		font_size = font_size * PANGO_SCALE;
	PangoLayout *layout = pango_cairo_create_layout(cr);
	PangoAttrColor *foreground_color = pango_attr_foreground_new(
			65535 * color->red, 65535 * color->green, 65535 * color->blue);
	PangoAttribute *foreground_alpha = pango_attr_foreground_alpha_new(
			65535 * color->alpha);
	PangoAttribute *font = pango_attr_family_new(pango_font_family_get_name(font_family));
	PangoAttribute *size = pango_attr_size_new(font_size);
	PangoAttrList *attr_list = pango_attr_list_new();
	PangoAttribute *attr;
	pango_attr_list_insert(attr_list, font);
	pango_attr_list_insert(attr_list, size);
	pango_attr_list_insert(attr_list, foreground_alpha);
	pango_layout_set_attributes(layout, attr_list);
	GString *subtitle=g_string_new("");

	g_regex_match(start_markup, subtitle_text_line, 0, &info);
	while (g_match_info_matches(info)) {
		temp = g_match_info_fetch(info, 0);
		g_match_info_fetch_pos(info, 0, &s, &e);
		remove_white_space(temp);
		temp2 = g_utf8_strdown(temp, -1);
		g_free(temp);
		temp = temp2;
		len = s - p;
		if (len > 0) {
			s=subtitle->len;
			if (format & Subtitle_Format_Bold){
				attr=pango_attr_weight_new(PANGO_WEIGHT_BOLD);
				attr->start_index=s;
				attr->end_index=s+len;
				pango_attr_list_insert(attr_list, attr);
			}

			if (format & Subtitle_Format_Itatic){
				attr=pango_attr_style_new(PANGO_STYLE_ITALIC);
				attr->start_index=s;
				attr->end_index=s+len;
				pango_attr_list_insert(attr_list, attr);
			}

			if (format & Subtitle_Format_Underline)
			{
				attr=pango_attr_underline_new(PANGO_UNDERLINE_SINGLE);
				attr->start_index=s;
				attr->end_index=s+len;
				pango_attr_list_insert(attr_list, attr);
			}
			foreground_color->attr.start_index=s;
			foreground_color->attr.end_index=s+len;
			pango_attr_list_insert(attr_list, pango_attribute_copy(foreground_color));
			g_string_append_len(subtitle,subtitle_text_line + p,len);
		}
		p = e;
		if (g_strstr_len(temp, -1, "</")) {
			format = GPOINTER_TO_UINT(g_queue_pop_tail(queue));
			if((format&Subtitle_Format_Special_Color)==0){
				foreground_color->color.red = color->red * 65535;
				foreground_color->color.green = color->green * 65535;
				foreground_color->color.blue = color->blue * 65535;
			}
		} else {
			g_queue_push_tail(queue, GUINT_TO_POINTER(format));
			temp2 = g_strstr_len(temp, -1, "<fontcolor=");
			if (temp2 != NULL) {
				temp2 = g_strstr_len(temp, -1, "=");
				format|=Subtitle_Format_Special_Color;
				temp2++;
				if (*temp2 == '"')
					temp2++;
				temp3 = temp2;
				while (*temp3 != '"' && *temp3 != '>')
					temp3++;
				len = temp3 - temp2;
				temp3 = g_strndup(temp2, len);
				pango_color_parse(&foreground_color->color, temp3);
				g_free(temp3);
			}
			if (g_strstr_len(temp, -1, "<i>")) {
				format |= Subtitle_Format_Itatic;
			};
			if (g_strstr_len(temp, -1, "<b>")) {
				format |= Subtitle_Format_Bold;
			};
			if (g_strstr_len(temp, -1, "<u>")) {
				format |= Subtitle_Format_Underline;
			};
		}
		g_free(temp);
		g_match_info_next(info, NULL);
	}

	len = g_utf8_strlen(subtitle_text_line,-1) - p;
	if (len > 0) {
		s=subtitle->len;

		if (format & Subtitle_Format_Bold){
			attr=pango_attr_weight_new(PANGO_WEIGHT_BOLD);
			attr->start_index=s;
			attr->end_index=s+len;
			pango_attr_list_insert(attr_list, attr);
		}

		if (format & Subtitle_Format_Itatic){
			attr=pango_attr_style_new(PANGO_STYLE_ITALIC);
			attr->start_index=s;
			attr->end_index=s+len;
			pango_attr_list_insert(attr_list, attr);
		}

		if (format & Subtitle_Format_Underline)
		{
			attr=pango_attr_underline_new(PANGO_UNDERLINE_SINGLE);
			attr->start_index=s;
			attr->end_index=s+len;
			pango_attr_list_insert(attr_list, attr);
		}
		foreground_color->attr.start_index=s;
		foreground_color->attr.end_index=s+len;
		pango_attr_list_insert(attr_list, foreground_color);
		g_string_append_len(subtitle,subtitle_text_line + p,len);
	}
	font->end_index=subtitle->len;
	size->end_index=subtitle->len;
	pango_layout_set_text(layout,subtitle->str,subtitle->len);
	g_queue_free(queue);
	pango_attr_list_unref(attr_list);
	g_string_free(subtitle,TRUE);
	g_match_info_free(info);
	g_regex_unref(start_markup);
	return layout;
}
