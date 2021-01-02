/*
 * MyTraceBar.c
 *
 *  Created on: 2021年1月2日
 *      Author: tom
 */

#include "MyTraceBar.h"

typedef struct {
	gfloat begin,end;
}MyTraceBarRange;

typedef struct {
	gfloat min, max, value;
	GHashTable *table;
} MyTraceBarPrivate;

typedef enum{
	MyTraceBarName,
	MyTraceBarMax,
	MyTraceBarMin,
	MyTraceBarValue,
}MyTraceBarProperty;

G_DEFINE_TYPE_WITH_CODE(MyTraceBar, my_trace_bar, GTK_TYPE_DRAWING_AREA,
		G_ADD_PRIVATE(MyTraceBar));

void my_trace_bar_set_property(MyTraceBar *self, guint property_id,
		const GValue *value, GParamSpec *pspec) {
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(self);
	switch (property_id){
	case MyTraceBarMax:
	case MyTraceBarMin:
	case MyTraceBarName:
	case MyTraceBarValue:
	default:G_OBJECT_WARN_INVALID_PROPERTY_ID(self,property_id,pspec);break;
	}

}
;
void my_trace_bar_get_property(MyTraceBar *self, guint property_id,
		GValue *value, GParamSpec *pspec) {
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(self);
	switch (property_id){
	case MyTraceBarMax:
	case MyTraceBarMin:
	case MyTraceBarName:
	case MyTraceBarValue:
	default:G_OBJECT_WARN_INVALID_PROPERTY_ID(self,property_id,pspec);break;
	}
}
;
void my_trace_bar_dispose(MyTraceBar *self) {
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(self);

}
;
void my_trace_bar_finalize(MyTraceBar *self) {
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(self);
	g_hash_table_remove_all(priv->table);
}
;

gboolean my_trace_bar_draw(MyTraceBar *self, cairo_t *cr) {
	MyTraceBarClass *class = MY_TRACE_BAR_GET_CLASS(self);
	GtkAllocation alloc;
	gtk_widget_get_allocation(self, &alloc);

	return GTK_WIDGET_CLASS(&class->parent_class)->draw(self, cr);
}

static void my_trace_bar_class_init(MyTraceBarClass *klass) {
	GtkWidgetClass *widget_lass = klass;
	GObjectClass *obj_class = klass;
	obj_class->get_property = my_trace_bar_get_property;
	obj_class->set_property = my_trace_bar_set_property;
	obj_class->dispose = my_trace_bar_dispose;
	obj_class->finalize = my_trace_bar_finalize;
	widget_lass->draw = my_trace_bar_draw;

}

static void my_trace_bar_init(MyTraceBar *self) {
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(self);
	priv->table=g_hash_table_new_full(g_direct_hash,g_direct_equal,g_object_unref,g_free);
}
