/*
 * srt_subtitle.h
 *
 *  Created on: 2021年1月8日
 *      Author: tom
 */

#ifndef SUBTITLE_SRT_SUBTITLE_H_
#define SUBTITLE_SRT_SUBTITLE_H_
#include "glib.h"
#include "glib-object.h"
#include "subtitle.h"
G_BEGIN_DECLS
typedef enum{
	Srt_Font=1,
	Srt_Color,
}SrtFormat;


#define MY_TYPE_SRT_SUBTITLE my_srt_subtitle_get_type()
G_DECLARE_DERIVABLE_TYPE(MySrtSubtitle,my_srt_subtitle,MY,SRT_SUBTITLE,GObject)
typedef struct _MySrtSubtitleClass{
	GObjectClass parent_class;
};


G_END_DECLS

#endif /* SUBTITLE_SRT_SUBTITLE_H_ */
