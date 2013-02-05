# makefile for awkGL

AWK_H_DIR = ${HOME}/gawk-4.0.1

CC = gcc
CFLAGS = -Wall -fPIC -shared -c -O2 -DHAVE_STRING_H -DHAVE_SNPRINTF -DHAVE_STDARG_H -DHAVE_VPRINTF -DDYNAMIC -I${AWK_H_DIR} -DHAVE_FREEGLUT
LDFLAGS = -shared -lglut -lGLU -lGL -lXext -lX11 -lm -lpthread

all: awkgl.so
	gawk 'BEGIN{ extension("./awkgl.so", "dlload") }'

awkgl.so: awkgl.c
	${CC} $< ${CFLAGS}
	${CC} awkgl.o -o $@ ${LDFLAGS}


.PHONY:clean
clean:
	rm awkgl.o awkgl.so
