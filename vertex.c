/*
 * vertex.c
 */

#include "awkgl.h"

NODE *do_Begin(int);
NODE *do_End(int);
NODE *do_Vertex2d(int);
NODE *do_Vertex3d(int);

NODE *
do_Begin(int nargs)
{
	NODE *tmp;
	char *str;
	GLenum type;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);
	str = tmp->stptr;

	if (!strcmp(str, "POINTS")) {
		type = GL_POINTS;
	} else if (!strcmp(str, "LINES")) {
		type = GL_LINES;
	} else if (!strcmp(str, "LINE_STRIP")) {
		type = GL_LINE_STRIP;
	} else if (!strcmp(str, "LINE_LOOP")) {
		type = GL_LINE_LOOP;
	} else if (!strcmp(str, "TRIANGLES")) {
		type = GL_TRIANGLES;
	} else if (!strcmp(str, "QUADS")) {
		type = GL_QUADS;
	} else if (!strcmp(str, "POLYGON")) {
		type = GL_POLYGON;
	} else if (!strcmp(str, "TRIANGLE_FAN")) {
		type = GL_TRIANGLE_FAN;
	} else {
		fatal(_("Begin: Invalid mode"));
		type = 0; /* suppress warning */
	}

	glBegin(type);
	return make_number((AWKNUM) 0);
}

NODE *
do_End(int nargs)
{
	glEnd();
	return make_number((AWKNUM) 0);
}

NODE *
do_Vertex2d(int nargs)
{
	NODE *tmp;
	GLdouble val1, val2;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	val1 = (GLdouble) force_number(tmp);
	tmp  = (NODE*) get_actual_argument(1, FALSE, FALSE);
	val2 = (GLdouble) force_number(tmp);

	glVertex2d(val1, val2);
	return make_number((AWKNUM) 0);
}

NODE *
do_Vertex3d(int nargs)
{
	NODE *tmp;
	GLdouble val1, val2, val3;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	val1 = (GLdouble) force_number(tmp);
	tmp  = (NODE*) get_actual_argument(1, FALSE, FALSE);
	val2 = (GLdouble) force_number(tmp);
	tmp  = (NODE*) get_actual_argument(2, FALSE, FALSE);
	val3 = (GLdouble) force_number(tmp);

	glVertex3d(val1, val2, val3);
	return make_number((AWKNUM) 0);
}
