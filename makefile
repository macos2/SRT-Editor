PKG-CONFIG:=$(shell pkg-config --libs --cflags gtk+-3.0 gstreamer-1.0 gstreamer-base-1.0 )# gstreamer-video-1.0
all:
	@make -C UI
	gcc $(shell find *.c */*.c) -o SRT-Editor $(PKG-CONFIG) -w -no-pie -g
