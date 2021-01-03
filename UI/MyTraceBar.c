/*
 * MyTraceBar.c
 *
 *  Created on: 2021年1月2日
 *      Author: tom
 */

#include "MyTraceBar.h"

typedef struct {
	gfloat start,end;
	gchar *describe;
	GdkRGBA color;
}MyTraceBarRange;

typedef struct {
	gfloat min, max, value;
	GHashTable *table;
	gchar *describe;
} MyTraceBarPrivate;

typedef enum{
	MyTraceBarDescribe=1,
	MyTraceBarMax,
	MyTraceBarMin,
	MyTraceBarValue,
}MyTraceBarProperty;

G_DEFINE_TYPE_WITH_CODE(MyTraceBar, my_trace_bar, GTK_TYPE_DRAWING_AREA,
		G_ADD_PRIVATE(MyTraceBar));

MyTraceBarRange *my_trace_bar_range_new(gfloat start,gfloat end,gchar *describe,gdouble r,gdouble g,gdouble b,gdouble alpha){
	MyTraceBarRange *range=g_malloc(sizeof(MyTraceBarRange));
	range->start=start;
	range->end=end;
	range->describe=g_strdup(describe);
	range->color.alpha=alpha;
	range->color.red=r;
	range->color.blue=b;
	range->color.green=g;
	return range;
}

void my_trace_bar_range_free(MyTraceBarRange *range){
	g_free(range->describe);
	g_free(range);
}

void my_trace_bar_set_property(MyTraceBar *self, guint property_id,
		const GValue *value, GParamSpec *pspec) {
	MyTraceBarClass *class=MY_TRACE_BAR_GET_CLASS(self);
	gfloat temp;
	gchar *temp_describe;
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(self);
	switch (property_id){
	case MyTraceBarMax:
		temp=g_value_get_float(value);
		if(temp>priv->min){
			priv->max=temp;
		g_object_notify(self,"max");
		}
		break;
	case MyTraceBarMin:
		temp=g_value_get_float(value);
		if(temp<priv->max){
			priv->min=temp;
			g_object_notify(self,"min");
		}
		break;
	case MyTraceBarDescribe:
		temp_describe=g_value_get_string(value);
		if(priv->describe!=NULL)g_free(priv->describe);
		priv->describe=g_strdup(temp_describe);
		g_object_notify(self,"describe");
		break;
	case MyTraceBarValue:
		temp=g_value_get_float(value);
		if(temp<priv->min){//smaller than min
			priv->value=priv->min;
		}else if(temp>priv->max){//bigger than max
			priv->value=priv->max;
		}else{ //correct value between min and max
			priv->value=temp;
		};
		g_object_notify(self,"value");
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(self,property_id,pspec);
		//G_OBJECT_CLASS(&class->parent_class)->set_property(self,property_id,value,pspec);
		;break;
	}
	gtk_widget_queue_draw(self);
}
;
void my_trace_bar_get_property(MyTraceBar *self, guint property_id,
		GValue *value, GParamSpec *pspec) {
	MyTraceBarClass *class=MY_TRACE_BAR_GET_CLASS(self);
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(self);
	switch (property_id){
	case MyTraceBarMax:
		g_value_init(value,G_TYPE_FLOAT);
		g_value_set_float(value,priv->max);
		break;
	case MyTraceBarMin:
		g_value_init(value,G_TYPE_FLOAT);
		g_value_set_float(value,priv->min);
		break;
	case MyTraceBarDescribe:
		g_value_init(value,G_TYPE_STRING);
		g_value_set_string(value,priv->describe);
		break;
	case MyTraceBarValue:
		g_value_init(value,G_TYPE_FLOAT);
		g_value_set_float(value,priv->value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(self,property_id,pspec);
		//G_OBJECT_CLASS(&class->parent_class)->get_property(self,property_id,value,pspec);
		break;
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
	g_free(priv->describe);
	priv->describe=NULL;
}
;

gboolean my_trace_bar_draw(MyTraceBar *self, cairo_t *cr) {
	MyTraceBarClass *class = MY_TRACE_BAR_GET_CLASS(self);
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(self);
	cairo_text_extents_t text_ex;
	gchar temp[10];
	GtkAllocation alloc;
	gint i=0;
	GHashTableIter iter;
	MyTraceBarRange *range;
	gtk_widget_get_allocation(self, &alloc);
	cairo_save(cr);
	cairo_set_source_rgb(cr,1.,0.9,0.);
	cairo_rectangle(cr,0,0,alloc.width,alloc.height);
	cairo_fill(cr);
	cairo_restore(cr);

	cairo_save(cr);
	cairo_set_font_size(cr,20);
	cairo_set_source_rgba(cr,0.2,0.2,1.0,0.2);
	cairo_text_extents(cr,priv->describe,&text_ex);
	cairo_translate(cr,10,(alloc.height+text_ex.height)/2.);
	cairo_show_text(cr,priv->describe);
	cairo_restore(cr);

	cairo_save(cr);
	cairo_set_source_rgba(cr,0.,0.,0.5,0.5);
	cairo_save(cr);
	for(i=0;i<101;i++){
		cairo_move_to(cr,0,0);
		cairo_line_to(cr,0,5);
		cairo_translate(cr,alloc.width/100.,0);
	}
	cairo_stroke(cr);

	cairo_restore(cr);
	cairo_set_font_size(cr,15);
	for(i=0;i<11;i++){
		cairo_move_to(cr,0,0);
		cairo_line_to(cr,0,10);
		g_sprintf(temp,"%.2f\0",i*(priv->max-priv->min)/10.+priv->min);
		cairo_text_extents(cr,temp,&text_ex);
		switch(i){
		case 0:
			cairo_move_to(cr,0,12+text_ex.height);
			break;
		case 10:
			cairo_move_to(cr,text_ex.width*-1.,12+text_ex.height);
			break;
		default:
		cairo_move_to(cr,text_ex.width/-2.,12+text_ex.height);
		break;
		}
		cairo_show_text(cr,temp);
		cairo_translate(cr,alloc.width/10.,0);
	}
	cairo_stroke(cr);
	cairo_restore(cr);

	cairo_save(cr);
	g_hash_table_iter_init(&iter,priv->table);
	cairo_scale(cr,alloc.width/(priv->max-priv->min),1.0);
	while(g_hash_table_iter_next(&iter,NULL,&range)){
		cairo_set_source_rgba(cr,range->color.red,range->color.green,range->color.blue,range->color.alpha);
		cairo_rectangle(cr,range->start-priv->min,26.,range->end-range->start,20);
		cairo_fill(cr);
	}
	cairo_restore(cr);

	cairo_save(cr);
	cairo_set_source_rgba(cr,0,0,1.,0.7);
	cairo_set_line_width(cr,5);
	cairo_move_to(cr,priv->value*alloc.width/(priv->max-priv->min),0);
	cairo_line_to(cr,priv->value*alloc.width/(priv->max-priv->min),alloc.height);
	cairo_stroke(cr);
	cairo_restore(cr);


	return TRUE;// GTK_WIDGET_CLASS(&class->parent_class)->draw(self, cr);
}

static void my_trace_bar_class_init(MyTraceBarClass *klass) {
	GtkWidgetClass *widget_lass = klass;
	GObjectClass *obj_class = klass;
	obj_class->get_property = my_trace_bar_get_property;
	obj_class->set_property = my_trace_bar_set_property;
	obj_class->dispose = my_trace_bar_dispose;
	obj_class->finalize = my_trace_bar_finalize;
	widget_lass->draw = my_trace_bar_draw;
	g_object_class_install_property(klass,MyTraceBarMax,g_param_spec_float("max","max","the max vaule of the bar",-1.*G_MAXFLOAT,G_MAXFLOAT,100.,G_PARAM_READWRITE|G_PARAM_CONSTRUCT));
	g_object_class_install_property(klass,MyTraceBarMin,g_param_spec_float("min","min","the min vaule of the bar",-1.*G_MAXFLOAT,G_MAXFLOAT,0.,G_PARAM_READWRITE|G_PARAM_CONSTRUCT));
	g_object_class_install_property(klass,MyTraceBarDescribe,g_param_spec_string("describe","describe","the describe of the bar","\0",G_PARAM_READWRITE|G_PARAM_CONSTRUCT));
	g_object_class_install_property(klass,MyTraceBarValue,g_param_spec_float("value","value","the vaule of the bar",-1.*G_MAXFLOAT,G_MAXFLOAT,0.,G_PARAM_READWRITE|G_PARAM_CONSTRUCT));
}

static void my_trace_bar_init(MyTraceBar *self) {
	MyTraceBarPrivate *priv=my_trace_bar_get_instance_private(self);
	priv->table=g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,my_trace_bar_range_free);
	priv->max=100.;
	priv->min=0.;
	priv->value=0.;
	priv->describe=g_strdup("\0");
	gtk_widget_set_size_request(self,100,48);
	g_hash_table_insert(priv->table,self,my_trace_bar_range_new(20.,30.,"debug",0.5,0.3,0.8,0.7));
	gtk_widget_add_events(self,GDK_BUTTON_PRESS_MASK|GDK_POINTER_MOTION_MASK|GDK_BUTTON1_MOTION_MASK |GDK_BUTTON2_MOTION_MASK |GDK_BUTTON3_MOTION_MASK);
}

MyTraceBar *my_trace_bar_new(gchar *describe){
	MyTraceBar *bar=g_object_new(MY_TYPE_TRACE_BAR,"describe",describe,NULL);
	return bar;
}
