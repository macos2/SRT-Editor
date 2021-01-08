/*
 * MyTraceBar.c
 *
 *  Created on: 2021年1月2日
 *      Author: tom
 */

#include "../ui/MyTraceBar.h"

typedef struct {
	gdouble start, end;
	gchar *describe;
	GdkRGBA color;
} MyTraceBarRange;

typedef struct {
	gdouble min, max, value;
	GHashTable *table;
	gchar *describe;
	gdouble press_x, press_y, motion_x, motion_y;
	guint select_index, press_button;
	gpointer selected_key;
	gpointer preselected_key;
	gboolean adj_range_max;
	gboolean adj_range_min;
	gboolean actived_notify;
} MyTraceBarPrivate;

typedef enum {
	MyTraceBarDescribe = 1, MyTraceBarMax, MyTraceBarMin, MyTraceBarValue,
} MyTraceBarProperty;

G_DEFINE_TYPE_WITH_CODE(MyTraceBar, my_trace_bar, GTK_TYPE_DRAWING_AREA,
		G_ADD_PRIVATE(MyTraceBar));

MyTraceBarRange* my_trace_bar_range_new(gdouble start, gdouble end,
		gchar *describe, gdouble r, gdouble g, gdouble b, gdouble alpha) {
	MyTraceBarRange *range = g_malloc(sizeof(MyTraceBarRange));
	range->start = start;
	range->end = end;
	range->describe = g_strdup(describe);
	range->color.alpha = alpha;
	range->color.red = r;
	range->color.blue = b;
	range->color.green = g;
	return range;
}

void my_trace_bar_range_free(MyTraceBarRange *range) {
	g_free(range->describe);
	g_free(range);
}

void my_trace_bar_set_property(MyTraceBar *self, guint property_id,
		const GValue *value, GParamSpec *pspec) {
	MyTraceBarClass *class = MY_TRACE_BAR_GET_CLASS(self);
	gdouble temp;
	gchar *temp_describe;
	MyTraceBarPrivate *priv = my_trace_bar_get_instance_private(self);
	switch (property_id) {
	case MyTraceBarMax:
		temp = g_value_get_double(value);
		if (temp > priv->min) {
			priv->max = temp;
			g_object_notify(self, "max");
		}
		break;
	case MyTraceBarMin:
		temp = g_value_get_double(value);
		if (temp < priv->max) {
			priv->min = temp;
			g_object_notify(self, "min");
		}
		break;
	case MyTraceBarDescribe:
		temp_describe = g_value_get_string(value);
		if (priv->describe != NULL)
			g_free(priv->describe);
		priv->describe = g_strdup(temp_describe);
		g_object_notify(self, "describe");
		break;
	case MyTraceBarValue:
		temp = g_value_get_double(value);
		if (temp < priv->min) { //smaller than min
			priv->value = priv->min;
		} else if (temp > priv->max) { //bigger than max
			priv->value = priv->max;
		} else { //correct value between min and max
			priv->value = temp;
		}
		;
		g_object_notify(self, "value");
		priv->actived_notify=FALSE;
		break;
	default:
		//G_OBJECT_WARN_INVALID_PROPERTY_ID(self,property_id,pspec);
		G_OBJECT_CLASS(&class->parent_class)->set_property(self, property_id,
				value, pspec);
		;
		break;
	}
	gtk_widget_queue_draw(self);
}
;
void my_trace_bar_get_property(MyTraceBar *self, guint property_id,
		GValue *value, GParamSpec *pspec) {
	MyTraceBarClass *class = MY_TRACE_BAR_GET_CLASS(self);
	MyTraceBarPrivate *priv = my_trace_bar_get_instance_private(self);
	switch (property_id) {
	case MyTraceBarMax:
		g_value_init(value, G_TYPE_DOUBLE);
		g_value_set_double(value, priv->max);
		break;
	case MyTraceBarMin:
		g_value_init(value, G_TYPE_DOUBLE);
		g_value_set_double(value, priv->min);
		break;
	case MyTraceBarDescribe:
		g_value_init(value, G_TYPE_STRING);
		g_value_set_string(value, priv->describe);
		break;
	case MyTraceBarValue:
		g_value_init(value, G_TYPE_DOUBLE);
		g_value_set_double(value, priv->value);
		break;
	default:
		//G_OBJECT_WARN_INVALID_PROPERTY_ID(self,property_id,pspec);
		G_OBJECT_CLASS(&class->parent_class)->get_property(self, property_id,
				value, pspec);
		break;
	}
}
;
void my_trace_bar_dispose(MyTraceBar *self) {
	MyTraceBarPrivate *priv = my_trace_bar_get_instance_private(self);

}
;
void my_trace_bar_finalize(MyTraceBar *self) {
	MyTraceBarPrivate *priv = my_trace_bar_get_instance_private(self);
	g_hash_table_remove_all(priv->table);
	g_free(priv->describe);
	priv->describe = NULL;
}
;

void my_trace_bar_draw_range(MyTraceBar *self, MyTraceBarRange *range,
		cairo_t *cr, gdouble x_unit,gdouble alpha) {
	MyTraceBarPrivate *priv = my_trace_bar_get_instance_private(self);
	cairo_text_extents_t text_ex;
	cairo_save(cr);
	cairo_rectangle(cr, (range->start - priv->min) * x_unit, 26.,
			(range->end - range->start) * x_unit, 36);
	cairo_set_source_rgba(cr, range->color.red, range->color.green,
			range->color.blue, range->color.alpha*alpha);
	cairo_fill(cr);
	cairo_set_source_rgba(cr, 0, 0, 0, 0.5);
	cairo_set_font_size(cr, 16);
	cairo_text_extents(cr, range->describe, &text_ex);
	cairo_move_to(cr,
			(range->start * x_unit + range->end * x_unit - text_ex.width) / 2.0,
			26. + 18. + text_ex.height / 2.0);
	cairo_show_text(cr, range->describe);
	cairo_restore(cr);
}

void my_trace_bar_draw_preselected_range(MyTraceBar *self,
		MyTraceBarRange *range, cairo_t *cr, gdouble x_unit) {
	MyTraceBarPrivate *priv = my_trace_bar_get_instance_private(self);
	cairo_text_extents_t text_ex;
	cairo_save(cr);
	my_trace_bar_draw_range(self, range, cr, x_unit,0.8);
	cairo_set_source_rgb(cr, 1., 1., 1.);
	cairo_set_line_width(cr, 4.);
	if (abs(priv->motion_x - range->start * x_unit) < 3) {
		cairo_move_to(cr, range->start * x_unit, 26);
		cairo_line_to(cr, range->start * x_unit, 62);
	} else if (abs(range->end * x_unit - priv->motion_x) < 3) {
		cairo_move_to(cr, range->end * x_unit, 26);
		cairo_line_to(cr, range->end * x_unit, 62);
	} else {
		cairo_rectangle(cr, (range->start - priv->min) * x_unit, 26.,
				(range->end - range->start) * x_unit, 36);
	}
	cairo_stroke(cr);
	cairo_restore(cr);
}

void my_trace_bar_draw_selected_range(MyTraceBar *self, MyTraceBarRange *range,
		cairo_t *cr, gdouble x_unit) {
	MyTraceBarPrivate *priv = my_trace_bar_get_instance_private(self);
	cairo_text_extents_t text_ex;
	cairo_save(cr);
	my_trace_bar_draw_range(self, range, cr, x_unit,0.8);

	cairo_set_line_width(cr, 2.);
	priv->adj_range_max = FALSE;
	priv->adj_range_min = FALSE;
	if (abs(priv->motion_x - range->start * x_unit) < 3) {
		cairo_set_source_rgb(cr, 0., 1., 0.3);
		cairo_move_to(cr, range->start * x_unit, 26);
		cairo_line_to(cr, range->start * x_unit, 62);
		priv->adj_range_min = TRUE;
	} else if (abs(range->end * x_unit - priv->motion_x) < 3) {
		cairo_set_source_rgb(cr, 0.3,0.,1. );
		cairo_move_to(cr, range->end * x_unit, 26);
		cairo_line_to(cr, range->end * x_unit, 62);
		priv->adj_range_max = TRUE;
	} else {
		cairo_set_source_rgb(cr, 1., 0.3, 0.);
		cairo_rectangle(cr, (range->start - priv->min) * x_unit, 26.,
				(range->end - range->start) * x_unit, 36);
	}
	cairo_stroke(cr);
	cairo_restore(cr);

}

gboolean my_trace_bar_draw(MyTraceBar *self, cairo_t *cr) {
	MyTraceBarClass *class = MY_TRACE_BAR_GET_CLASS(self);
	MyTraceBarPrivate *priv = my_trace_bar_get_instance_private(self);
	cairo_text_extents_t text_ex;
	gchar temp[10];
	GtkAllocation alloc;
	gint i = 0;
	GHashTableIter iter;
	MyTraceBarRange *range;
	gpointer key, preselected_key = NULL,selected_key;
	GList *mouse_in_range = NULL;
	gdouble unit;
	GdkRectangle rectangle;
	gtk_widget_get_allocation(self, &alloc);
	cairo_save(cr);
	cairo_set_source_rgb(cr, 1., 0.9, 0.);
	cairo_rectangle(cr, 0, 0, alloc.width, alloc.height);
	cairo_fill(cr);
	cairo_restore(cr);

	cairo_save(cr);
	cairo_set_font_size(cr, 20);
	cairo_set_source_rgba(cr, 0.2, 0.2, 1.0, 0.2);
	cairo_text_extents(cr, priv->describe, &text_ex);
	cairo_translate(cr, 10, (alloc.height + text_ex.height) / 2.);
	cairo_show_text(cr, priv->describe);
	cairo_restore(cr);

	cairo_save(cr);
	cairo_set_source_rgba(cr, 0., 0., 0.5, 0.5);
	cairo_save(cr);
	for (i = 0; i < 101; i++) {
		cairo_move_to(cr, 0, 0);
		cairo_line_to(cr, 0, 5);
		cairo_translate(cr, alloc.width / 100., 0);
	}
	cairo_stroke(cr);

	cairo_restore(cr);
	cairo_set_font_size(cr, 15);
	for (i = 0; i < 11; i++) {
		cairo_move_to(cr, 0, 0);
		cairo_line_to(cr, 0, 10);
		g_sprintf(temp, "%.2lf\0",
				i * (priv->max - priv->min) / 10. + priv->min);
		cairo_text_extents(cr, temp, &text_ex);
		switch (i) {
		case 0:
			cairo_move_to(cr, 0, 12 + text_ex.height);
			break;
		case 10:
			cairo_move_to(cr, text_ex.width * -1., 12 + text_ex.height);
			break;
		default:
			cairo_move_to(cr, text_ex.width / -2., 12 + text_ex.height);
			break;
		}
		cairo_show_text(cr, temp);
		cairo_translate(cr, alloc.width / 10., 0);
	}
	cairo_stroke(cr);
	cairo_restore(cr);

	cairo_save(cr);
	g_hash_table_iter_init(&iter, priv->table);
	//cairo_scale(cr, alloc.width / (priv->max - priv->min), 1.0);
	unit = alloc.width / (priv->max - priv->min);
	while (g_hash_table_iter_next(&iter, &key, &range)) {
		cairo_new_path (cr);
		cairo_rectangle(cr, (range->start - priv->min) * unit-3., 26.,
				(range->end - range->start) * unit+6., 36);
		if (cairo_in_fill(cr, priv->motion_x, priv->motion_y)) {
			mouse_in_range = g_list_append(mouse_in_range, key);
		} else {
			cairo_new_path (cr);
			my_trace_bar_draw_range(self, range, cr, unit,1.0);
		}
		if ((range->start < priv->value) && (priv->value < range->end))
			if(priv->actived_notify==FALSE)g_signal_emit_by_name(self, "obj_active", key, NULL);
	}
	cairo_new_path (cr);
	priv->actived_notify=TRUE;
	if (mouse_in_range != NULL && priv->press_button != 1) {
		mouse_in_range = g_list_first(mouse_in_range);
		i = priv->select_index;
		while (1) {
			preselected_key = mouse_in_range->data;
			if (i == 0)
				break;
			else {
				if (mouse_in_range->next != NULL)
					mouse_in_range = mouse_in_range->next;
				i--;
			}
		}
		mouse_in_range = g_list_first(mouse_in_range);
		while (1) {
			if (mouse_in_range->data != preselected_key){
				range = g_hash_table_lookup(priv->table, mouse_in_range->data);
				my_trace_bar_draw_range(self, range, cr, unit,1.0);
			}
			if (mouse_in_range->next != NULL)
				mouse_in_range = mouse_in_range->next;
			else
				break;
		}
		range = g_hash_table_lookup(priv->table,  preselected_key);
		my_trace_bar_draw_preselected_range(self, range, cr, unit);
//		if(priv->preselected_key!=preselected_key){
//			g_signal_emit_by_name(self,"obj_unpreselected",priv->preselected_key);
			rectangle.height=36;
			rectangle.width=(gint)(range->end - range->start) * unit;
			rectangle.x= (gint)(range->start - priv->min) * unit;
			rectangle.y=26;
			g_signal_emit_by_name(self,"obj_preselected",preselected_key,&rectangle,NULL);
//		}
		priv->preselected_key=preselected_key;
	}

	if (mouse_in_range != NULL && priv->press_button == 1) {
		if (priv->selected_key == NULL) {
			//there are no key range have been selected beforce,detect the select key by the select index
			while (1) {
				if (priv->select_index == 0) //the key have been selected
					break;
				priv->select_index--;
				if (mouse_in_range->next != NULL)
					mouse_in_range = mouse_in_range->next;
			}
			selected_key = mouse_in_range->data;
		}else{
			selected_key=priv->selected_key;
		}
		mouse_in_range = g_list_first(mouse_in_range);
		while (1) { //draw the key range that haven't been selected.
			if (selected_key != mouse_in_range->data) {
				range = g_hash_table_lookup(priv->table, mouse_in_range->data);
				my_trace_bar_draw_range(self, range, cr, unit,1.0);
			}
			if (mouse_in_range->next == NULL)
				break;
			else
				mouse_in_range = mouse_in_range->next;
		}
		//draw the key range that have been selected.
		range = g_hash_table_lookup(priv->table,selected_key);
		my_trace_bar_draw_selected_range(self, range, cr, unit);
		if(priv->selected_key==NULL){
			rectangle.height=36;
			rectangle.width=(gint)(range->end - range->start) * unit;
			rectangle.x= (gint)(range->start - priv->min) * unit;
			rectangle.y=26;
			g_signal_emit_by_name(self,"obj_selected",selected_key,&rectangle,NULL);
			priv->selected_key=selected_key;
		}
	}

	if (mouse_in_range == NULL) {
		//the mouse is not in the key range area. clear the select index and selected_key.
		priv->press_button = 0;
		priv->select_index = 0;
		if(priv->selected_key!=NULL&&priv->motion_y>26.){
			g_signal_emit_by_name(self,"obj_unselected",priv->selected_key,NULL);
			priv->selected_key = NULL;
		}
		if(priv->preselected_key!=NULL){
			g_signal_emit_by_name(self,"obj_unpreselected",priv->preselected_key);
			priv->preselected_key=NULL;
		}

	}
	cairo_restore(cr);
	cairo_save(cr);
	cairo_set_source_rgba(cr, 0, 0, 1., 0.7);
	cairo_set_line_width(cr, 5);
	cairo_move_to(cr, priv->value * alloc.width / (priv->max - priv->min), 0);
	cairo_line_to(cr, priv->value * alloc.width / (priv->max - priv->min),
			alloc.height);
	cairo_stroke(cr);
	cairo_restore(cr);
	g_list_free(mouse_in_range);
	return TRUE; //GTK_WIDGET_CLASS(&class->parent_class)->draw(self, cr);
}

gboolean my_trace_bar_button_press(MyTraceBar *self, GdkEventButton *event) {
	MyTraceBarPrivate *priv = my_trace_bar_get_instance_private(self);
	priv->press_x = event->x;
	priv->press_y = event->y;
	priv->press_button = event->button;
	if (event->button == 3) {
		priv->select_index++;
	}
	//g_print("%d press:%lf %lf\n",event->button,event->x,event->y);
	gtk_widget_queue_draw(self);
	return TRUE;
}

gboolean my_trace_bar_button_release(MyTraceBar *self, GdkEventButton *event) {
	MyTraceBarPrivate *priv = my_trace_bar_get_instance_private(self);
	priv->press_button = 0;
	//g_print("buton release\n");
	return TRUE;
}
;

gboolean my_trace_bar_motion_notify(MyTraceBar *self, GdkEventMotion *event) {
	gdouble adj_unit;
	GtkAllocation alloc;
	MyTraceBarRange *range;
	MyTraceBarPrivate *priv = my_trace_bar_get_instance_private(self);
	priv->motion_x = event->x;
	priv->motion_y = event->y;
	if (priv->press_button == 1 && priv->selected_key != NULL) {
		gtk_widget_get_allocation(self, &alloc);
		adj_unit = (gdouble) (event->x - priv->press_x)
				* (priv->max - priv->min) / alloc.width;
		range = g_hash_table_lookup(priv->table, priv->selected_key);
		if (priv->adj_range_max && (range->end + adj_unit) > range->start) {
			range->end += adj_unit;
		} else if (priv->adj_range_min
				&& (range->start + adj_unit) < range->end) {
			range->start += adj_unit;
		} else {
			range->start += adj_unit;
			range->end += adj_unit;

		}
		priv->press_x = event->x;
		priv->press_y = event->y;
		g_signal_emit_by_name(self, "obj_range_change", priv->selected_key,
				range->start, range->end, NULL);

	}
	//g_print("motion:%lf %lf\n",event->x,event->y);
	gtk_widget_queue_draw(self);
	return TRUE;
}

static void my_trace_bar_class_init(MyTraceBarClass *klass) {
	GtkWidgetClass *widget_class = klass;
	GObjectClass *obj_class = klass;
	obj_class->get_property = my_trace_bar_get_property;
	obj_class->set_property = my_trace_bar_set_property;
	obj_class->dispose = my_trace_bar_dispose;
	obj_class->finalize = my_trace_bar_finalize;
	widget_class->draw = my_trace_bar_draw;
	widget_class->button_press_event = my_trace_bar_button_press;
	widget_class->motion_notify_event = my_trace_bar_motion_notify;
	widget_class->button_release_event = my_trace_bar_button_release;
	//widget_class->button_press_event
	g_object_class_install_property(klass, MyTraceBarMax,
			g_param_spec_double("max", "max", "the max vaule of the bar",
					-1. * G_MAXDOUBLE, G_MAXDOUBLE, 100.,
					G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
	g_object_class_install_property(klass, MyTraceBarMin,
			g_param_spec_double("min", "min", "the min vaule of the bar",
					-1. * G_MAXDOUBLE, G_MAXDOUBLE, 0.,
					G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
	g_object_class_install_property(klass, MyTraceBarDescribe,
			g_param_spec_string("describe", "describe",
					"the describe of the bar", "\0",
					G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
	g_object_class_install_property(klass, MyTraceBarValue,
			g_param_spec_double("value", "value", "the vaule of the bar",
					-1. * G_MAXDOUBLE, G_MAXDOUBLE, 0.,
					G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
	g_signal_new("obj_active", MY_TYPE_TRACE_BAR, G_SIGNAL_RUN_LAST,
			G_STRUCT_OFFSET(MyTraceBarClass, obj_active), NULL, NULL, NULL,
			G_TYPE_NONE, 1, G_TYPE_POINTER, NULL);
	g_signal_new("obj_selected", MY_TYPE_TRACE_BAR, G_SIGNAL_RUN_LAST,
			G_STRUCT_OFFSET(MyTraceBarClass, obj_selected), NULL, NULL, NULL,
			G_TYPE_NONE, 2, G_TYPE_POINTER, GDK_TYPE_RECTANGLE,NULL);
	g_signal_new("obj_preselected", MY_TYPE_TRACE_BAR, G_SIGNAL_RUN_LAST,
			G_STRUCT_OFFSET(MyTraceBarClass, obj_preselected), NULL, NULL, NULL,
			G_TYPE_NONE, 2, G_TYPE_POINTER, GDK_TYPE_RECTANGLE,NULL);
	g_signal_new("obj_unselected", MY_TYPE_TRACE_BAR, G_SIGNAL_RUN_LAST,
			G_STRUCT_OFFSET(MyTraceBarClass, obj_unselected), NULL, NULL, NULL,
			G_TYPE_NONE, 1, G_TYPE_POINTER, NULL);
	g_signal_new("obj_unpreselected", MY_TYPE_TRACE_BAR, G_SIGNAL_RUN_LAST,
			G_STRUCT_OFFSET(MyTraceBarClass, obj_unselected), NULL, NULL, NULL,
			G_TYPE_NONE, 1, G_TYPE_POINTER, NULL);
	g_signal_new("obj_range_change", MY_TYPE_TRACE_BAR, G_SIGNAL_RUN_LAST,
			G_STRUCT_OFFSET(MyTraceBarClass, obj_range_change), NULL, NULL,
			NULL, G_TYPE_NONE, 3, G_TYPE_POINTER, G_TYPE_DOUBLE, G_TYPE_DOUBLE,
			NULL);
	g_signal_new("obj_describe_change", MY_TYPE_TRACE_BAR, G_SIGNAL_RUN_LAST,
			G_STRUCT_OFFSET(MyTraceBarClass, obj_describe_change), NULL, NULL,
			NULL, G_TYPE_NONE, 2, G_TYPE_POINTER, G_TYPE_STRING, NULL);
	g_signal_new("obj_color_change", MY_TYPE_TRACE_BAR, G_SIGNAL_RUN_LAST,
			G_STRUCT_OFFSET(MyTraceBarClass, obj_color_change), NULL, NULL,
			NULL, G_TYPE_NONE, 2, G_TYPE_POINTER, G_TYPE_POINTER, NULL);
}

static void my_trace_bar_init(MyTraceBar *self) {
	MyTraceBarPrivate *priv = my_trace_bar_get_instance_private(self);
	priv->table = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL,
			my_trace_bar_range_free);
	priv->max = 100.;
	priv->min = 0.;
	priv->value = 0.;
	priv->describe = g_strdup("\0");
	priv->actived_notify=FALSE;
	gtk_widget_set_size_request(self, 100, 64);
	gtk_widget_add_events(self,
			GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK
					| GDK_BUTTON1_MOTION_MASK | GDK_BUTTON2_MOTION_MASK
					| GDK_BUTTON3_MOTION_MASK | GDK_BUTTON_RELEASE_MASK);
}

MyTraceBar* my_trace_bar_new(gchar *describe) {
	MyTraceBar *bar = g_object_new(MY_TYPE_TRACE_BAR, "describe", describe,
	NULL);
	return bar;
}

gdouble my_trace_bar_get_value(MyTraceBar *bar){
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(bar);
	return priv->value;
}

void my_trace_bar_set_value(MyTraceBar *bar,gdouble value){
g_object_set(bar,"value",value,NULL);
}
const gchar* my_trace_bar_get_describe(MyTraceBar *bar){
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(bar);
	return priv->describe;
}


void my_trace_bar_add_obj_range(MyTraceBar *bar,gpointer obj,gdouble start,gdouble end,const gchar *describe,const GdkRGBA *color){
	MyTraceBarRange *range=NULL;
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(bar);
	range=g_hash_table_lookup(priv->table,obj);
	if(range==NULL){
		range=my_trace_bar_range_new(start,end,describe,color->red,color->green,color->blue,color->alpha);
		g_hash_table_insert(priv->table,obj,range);
	}else{
		range->start=start;
		range->end=end;
		range->color.alpha=color->alpha;
		range->color.blue=color->blue;
		range->color.green=color->green;
		range->color.red=color->red;
		if(range->describe!=NULL)g_free(range->describe);
		range->describe=g_strdup(describe);
	}
}

void my_trace_bar_del_obj_range(MyTraceBar *bar,gpointer obj){
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(bar);
	g_hash_table_remove(priv->table,obj);
}

const gchar* my_trace_bar_get_obj_describe(MyTraceBar *bar,gpointer obj){
	MyTraceBarRange *range=NULL;
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(bar);
	range=g_hash_table_lookup(priv->table,obj);
	if(range!=NULL)return range->describe;
	return NULL;
}
void my_trace_bar_set_obj_describe(MyTraceBar *bar,gpointer obj,const gchar *describe){
	MyTraceBarRange *range=NULL;
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(bar);
	range=g_hash_table_lookup(priv->table,obj);
	if(range!=NULL){
		if(range->describe!=NULL)g_free(range->describe);
		range->describe=g_strdup(describe);
		g_signal_emit_by_name(bar,"obj_describe_change",obj,range->describe,NULL);
	};
}
void my_trace_bar_get_obj_range(MyTraceBar *bar,gpointer obj,gdouble *start,gdouble *end){
	MyTraceBarRange *range=NULL;
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(bar);
	range=g_hash_table_lookup(priv->table,obj);
	if(range!=NULL){
		*start=range->start;
		*end=range->end;
	}
}
void my_trace_bar_set_obj_range(MyTraceBar *bar,gpointer obj,const gdouble start,const gdouble end){
	MyTraceBarRange *range=NULL;
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(bar);
	range=g_hash_table_lookup(priv->table,obj);
	if(range!=NULL){
		range->start=start<end?start:end;
		range->end=start<end?end:start;
	}
}
const GdkRGBA *my_trace_bar_get_obj_color(MyTraceBar *bar,gpointer obj){
	MyTraceBarRange *range=NULL;
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(bar);
	range=g_hash_table_lookup(priv->table,obj);
	if(range!=NULL){
		return &range->color;
	}
	return NULL;
}
void my_trace_bar_set_obj_color(MyTraceBar *bar,gpointer obj,const GdkRGBA *color){
	MyTraceBarRange *range=NULL;
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(bar);
	range=g_hash_table_lookup(priv->table,obj);
	if(range!=NULL){
		range->color.alpha=color->alpha;
		range->color.blue=color->blue;
		range->color.green=color->green;
		range->color.red=color->red;
		g_signal_emit_by_name(bar,"obj_color_change",obj,&range->color,NULL);
	}
}


