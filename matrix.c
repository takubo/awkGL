/*
 * matrix.c
 */

#include "awkgl.h"

NODE *do_MatrixMode(int);
NODE *do_LoadIdentity(int);
NODE *do_PushMatrix(int);
NODE *do_PopMatrix(int);

NODE *do_MultMatrix(int);

NODE *do_Rotate(int);
NODE *do_Transrate(int);
NODE *do_Scale(int);

// 回転、移動、サイズ変更

NODE *
do_MatrixMode(int nargs)
{
	NODE *tmp;
	GLenum mode;

	if (do_lint && get_curfunc_arg_count() > 1)
		lintwarn("MatrixMode: called with too many arguments");

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);

	if (!strcmp(tmp->stptr, "MODELVIEW")) {
		/* モデルビュー行列 */
		mode = GL_MODELVIEW;
	} else if (!strcmp(tmp->stptr, "PROJECTION")) {
		/* 射影行列 */
		mode = GL_PROJECTION;
	} else if (!strcmp(tmp->stptr, "TEXTURE")) {
		/* テクスチャ行列 */
		mode = GL_TEXTURE;
	}

	glMatrixMode(mode);
	return make_number((AWKNUM) 0);
}

NODE *
do_LoadIdentity(int nargs)
{
	if (do_lint && get_curfunc_arg_count() > 0)
		lintwarn("LoadIdentity: called with too many arguments");

	glLoadIdentity();
	return make_number((AWKNUM) 0);
}

NODE *
do_PushMatrix(int nargs)
{
	if (do_lint && get_curfunc_arg_count() > 0)
		lintwarn("PushMatrix: called with too many arguments");

	glPushMatrix();
	return make_number((AWKNUM) 0);
}

NODE *
do_PopMatrix(int nargs)
{
	if (do_lint && get_curfunc_arg_count() > 0)
		lintwarn("PopMatrix: called with too many arguments");

	glPopMatrix();
	return make_number((AWKNUM) 0);
}

NODE *
do_MultMatrix(int nargs)
{
	NODE *tmp;
	int i;
	GLdouble m[16];

	for (i = 0; i < 16; i++) {
		tmp  = (NODE *) get_actual_argument(i, FALSE, FALSE);
		m[i] = (GLdouble) force_number(tmp);
	}

	glMultMatrixd(m);
	return make_number((AWKNUM) 0);
}

NODE *
do_Rotate(int nargs)
{
	NODE *tmp;
	GLdouble angle;
	GLdouble x;
	GLdouble y;
	GLdouble z;

	tmp   = (NODE*) get_actual_argument(0, FALSE, FALSE);
	angle = (GLdouble) force_number(tmp);
	tmp   = (NODE*) get_actual_argument(1, FALSE, FALSE);
	x     = (GLdouble) force_number(tmp);
	tmp   = (NODE*) get_actual_argument(2, FALSE, FALSE);
	y     = (GLdouble) force_number(tmp);
	tmp   = (NODE*) get_actual_argument(3, FALSE, FALSE);
	z     = (GLdouble) force_number(tmp);

	glRotated(angle, x, y, z);
	return make_number((AWKNUM) 0);
}

NODE *
do_Transrate(int nargs)
{
	NODE *tmp;
	GLdouble x;
	GLdouble y;
	GLdouble z;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	x   = (GLdouble) force_number(tmp);
	tmp = (NODE*) get_actual_argument(1, FALSE, FALSE);
	y   = (GLdouble) force_number(tmp);
	tmp = (NODE*) get_actual_argument(2, FALSE, FALSE);
	z   = (GLdouble) force_number(tmp);

	glTranslated(x, y, z);
	return make_number((AWKNUM) 0);
}

NODE *
do_Scale(int nargs)
{
	NODE *tmp;
	GLdouble x;
	GLdouble y;
	GLdouble z;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	x   = (GLdouble) force_number(tmp);
	tmp = (NODE*) get_actual_argument(1, FALSE, FALSE);
	y   = (GLdouble) force_number(tmp);
	tmp = (NODE*) get_actual_argument(2, FALSE, FALSE);
	z   = (GLdouble) force_number(tmp);

	glScaled(x, y, z);
	return make_number((AWKNUM) 0);
}
