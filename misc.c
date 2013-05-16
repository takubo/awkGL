/*
 * misc.c
 */

#include "awkgl.h"

NODE *do_SwapBuffers(int);

NODE *do_Enable(int);
NODE *do_Disable(int);
NODE *do_IsEnabled(int);
static GLenum str2cap(const char *);

NODE *do_PointSize(int);
NODE *do_LineWidth(int);
NODE *do_LineStipple(int);
NODE *do_PolygonMode(int);
static GLenum polygon_mode(const char *);

NODE *do_FrontFace(int);

NODE *do_CullFace(int);

NODE *do_PolygonOffset(int);

NODE *
do_SwapBuffers(int nargs)
{
	glutSwapBuffers();
	return make_number((AWKNUM) 0);
}

NODE *
do_Enable(int nargs)
{
	NODE *tmp;
	GLenum cap;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);
	//Todo
	cap = str2cap(tmp->stptr);

	glEnable(cap);
	return make_number((AWKNUM) 0);
}

NODE *
do_Disable(int nargs)
{
	NODE *tmp;
	GLenum cap;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);
	//Todo
	cap = str2cap(tmp->stptr);

	glDisable(cap);
	return make_number((AWKNUM) 0);
}

NODE *
do_IsEnabled(int nargs)
{
	NODE *tmp;
	GLenum cap;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);
	cap = str2cap(tmp->stptr);

	return make_number((AWKNUM) glIsEnabled(cap));
}

static GLenum
str2cap(const char *str)
{
	GLenum para;

	para = light_light_s(str);

	if (!strcmp(str, "LIGHTING")) {
		para = GL_LIGHTING;
	} else if (!strcmp(str, "POINT_SMOOTH")) {
		para = GL_POINT_SMOOTH;
	} else if (!strcmp(str, "LINE_SMOOTH")) {
		para = GL_LINE_SMOOTH;
	} else if (!strcmp(str, "POLYGON_OFFSET_FILL")) {
		para = GL_POLYGON_OFFSET_FILL;
	} else if (!strcmp(str, "POLYGON_OFFSET_LINE")) {
		para = GL_POLYGON_OFFSET_LINE;
	} else if (!strcmp(str, "POLYGON_OFFSET_POINT")) {
		para = GL_POLYGON_OFFSET_POINT;
	} else if (!strcmp(str, "CULL_FACE")) {
		para = GL_CULL_FACE;
	} else {
		fatal(_("Invalid capabilities"));
		para = 0; /* suppress warning */
	}

	return para;
}

NODE *
do_PointSize(int nargs)
{
	NODE *tmp;
	GLfloat size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLfloat) force_number(tmp);

	glPointSize(size);
	return make_number((AWKNUM) 0);
}

NODE *
do_LineWidth(int nargs)
{
	NODE *tmp;
	GLfloat width;

	tmp   = (NODE*) get_actual_argument(0, FALSE, FALSE);
	width = (GLfloat) force_number(tmp);

	glLineWidth(width);
	return make_number((AWKNUM) 0);
}

NODE *
do_LineStipple(int nargs)
{
	NODE     *tmp;
	GLint    factor;
	GLushort pattern = 0;
	int      i;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	factor = (GLint) force_number(tmp);

	tmp    = (NODE*) get_actual_argument(1, FALSE, FALSE);
	force_string(tmp);
	for (i = 0; i < 16; i++) {
		if (tmp->stptr[i] != '0' && tmp->stptr[i] != ' ') {
			pattern |= 1 << i;
		}
	}

	glLineStipple (factor, pattern);
	return make_number((AWKNUM) 0);
}

NODE *
do_PolygonMode(int nargs)
{
	NODE *tmp;
	GLenum face;
	GLenum mode;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);
	face = material_face(tmp->stptr);

	tmp  = (NODE*) get_actual_argument(1, FALSE, FALSE);
	force_string(tmp);
	mode = polygon_mode(tmp->stptr);

	glPolygonMode(face, mode);
	return make_number((AWKNUM) 0);
}

static GLenum
polygon_mode(const char *str)
{
	if (!strcmp(str, "POINT")) {
		return GL_POINT;
	} else if (!strcmp(str, "LINE")) {
		return GL_LINE;
	} else if (!strcmp(str, "FILL")) {
		return GL_FILL;
	} else {
		fatal(_("Invalid polygon mode."));
		return 0; /* suppress warning */
	}
}

NODE *
do_FrontFace(int nargs)
{
	NODE *tmp;
	const char *str;
	GLenum mode;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);

	str = tmp->stptr;

	skip_str(str, "GL_");

	if (!strcmp(str, "CCW")) {
		mode = GL_CCW;
	} else if (!strcmp(str, "CW")) {
		mode = GL_CW;
	} else {
		fatal(_("FrontFace(): Invalid mode."));
		mode = 0; /* suppress warning */
	}

	glFrontFace(mode);
	return make_number((AWKNUM) 0);
}

NODE *
do_CullFace(int nargs)
{
	NODE *tmp;
	GLenum mode;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);
	mode = material_face(tmp->stptr);

	glCullFace(mode);
	return make_number((AWKNUM) 0);
}

NODE *
do_PolygonOffset(int nargs)
{
	NODE *tmp;
	GLfloat factor;
	GLfloat units;

	tmp    = (NODE *) get_scalar_argument(0, FALSE);
	factor = (GLfloat) force_number(tmp);
	tmp    = (NODE *) get_scalar_argument(1, FALSE);
	units  = (GLfloat) force_number(tmp);

	glPolygonOffset(factor, units);
	return make_number((AWKNUM) 0);
}
