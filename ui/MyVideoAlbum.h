/*
 * MyVideoAlbum.h
 *
 *  Created on: 2021年1月31日
 *      Author: tom
 */

#ifndef UI_MYVIDEOALBUM_H_
#define UI_MYVIDEOALBUM_H_
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gst/gst.h>
#include <stdio.h>
G_BEGIN_DECLS
#define MY_TYPE_VIDEO_ALBUM my_video_album_get_type()
G_DECLARE_DERIVABLE_TYPE(MyVideoAlbum, my_video_album, MY, VIDEO_ALBUM,
		GtkWindow)

typedef struct _MyVideoAlbumClass {
	GtkWindowClass parent_class;
};

MyVideoAlbum* my_video_album_new();

G_END_DECLS
#endif /* UI_MYVIDEOALBUM_H_ */
