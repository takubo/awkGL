# makefile for awkGL

AWK_H_DIR = ${HOME}/gawk-4.0.1

CC = gcc
CFLAGS = -Wall -fPIC -shared -c -O2 -DHAVE_STRING_H -DHAVE_SNPRINTF -DHAVE_STDARG_H -DHAVE_VPRINTF -DDYNAMIC -I${AWK_H_DIR} -DHAVE_FREEGLUT -DGL_GLEXT_PROTOTYPES
LDFLAGS = -shared -lglut -lGLU -lGL -lXext -lX11 -lm -lpthread

all: awkgl.so
	gawk 'BEGIN{ extension("./awkgl.so", "dlload") }'

awkgl.so: awkgl.o bitmap.o device.o draw_geometry.o font.o loop.o material.o matrix.o misc.o util.o vertex.o view.o window.o
	${CC} $^ -o $@ ${LDFLAGS}

c.o:
	${CC} ${CFLAGS} $<

.PHONY:clean
clean:
	rm awkgl.so awkgl.o bitmap.o device.o draw_geometry.o font.o loop.o material.o matrix.o misc.o util.o vertex.o view.o window.o
