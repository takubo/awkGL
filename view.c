/*
 * view.c
 */

#include "awkgl.h"

NODE *do_Viewport(int);

NODE *do_Ortho(int);
NODE *do_Frustum(int);
NODE *do_Perspective(int);
NODE *do_Lookat(int);

NODE *
do_Viewport(int nargs)
{
	NODE *tmp;
	GLint x;
	GLint y;
	GLsizei w;
	GLsizei h;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	x      = (GLint) force_number(tmp);

	tmp    = (NODE*) get_actual_argument(1, FALSE, FALSE);
	y      = (GLint) force_number(tmp);

	tmp    = (NODE*) get_actual_argument(2, FALSE, FALSE);
	w      = (GLsizei) force_number(tmp);

	tmp    = (NODE*) get_actual_argument(3, FALSE, FALSE);
	h      = (GLsizei) force_number(tmp);
//printf("%d %d %d %d\n", x,y,w,h);
	glViewport(x, y, w, h);
	return make_number((AWKNUM) 0);
}

NODE *
do_Ortho(int nargs)
{
	NODE *tmp;

	GLdouble left;
	GLdouble right;
	GLdouble bottom;
	GLdouble top;
	GLdouble near;
	GLdouble far;

	tmp     = (NODE*) get_actual_argument(0, FALSE, FALSE);
	left    = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(1, FALSE, FALSE);
	right   = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(2, FALSE, FALSE);
	bottom  = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(3, FALSE, FALSE);
	top     = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(4, FALSE, FALSE);
	near    = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(5, FALSE, FALSE);
	far     = (GLdouble) (force_number(tmp));

//printf("%f %f %f %f %f %f  \n", left,right,bottom,top,near,far);
	glOrtho(left, right, bottom, top, near, far);
	return make_number((AWKNUM) 0);
}

NODE *
do_Frustum(int nargs)
{
	NODE *tmp;
	GLdouble left;
	GLdouble right;
	GLdouble bottom;
	GLdouble top;
	GLdouble near;
	GLdouble far;

	tmp     = (NODE*) get_actual_argument(0, FALSE, FALSE);
	left    = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(1, FALSE, FALSE);
	right   = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(2, FALSE, FALSE);
	bottom  = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(3, FALSE, FALSE);
	top     = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(4, FALSE, FALSE);
	near    = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(5, FALSE, FALSE);
	far     = (GLdouble) (force_number(tmp));

	//printf("%f %f %f %f %f %f  \n",
	//	left, right, bottom, top, near, far);

	glFrustum(left, right, bottom, top, near, far);
	return make_number((AWKNUM) 0);
}

NODE *
do_Perspective(int nargs)
{
	NODE *tmp;

	GLdouble angle;
	GLdouble aspect;
	GLdouble front;
	GLdouble back;

	tmp     = (NODE*) get_actual_argument(0, FALSE, FALSE);
	angle   = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(1, FALSE, FALSE);
	aspect  = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(2, FALSE, FALSE);
	front   = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(3, FALSE, FALSE);
	back    = (GLdouble) (force_number(tmp));

	//?glMatrixMode(GL_PROJECTION);
	//?glLoadIdentity();
	gluPerspective(angle, aspect, front, back);
	return make_number((AWKNUM) 0);
}

NODE *
do_Lookat(int nargs)
{
	NODE *tmp;

	GLdouble eyeX;
	GLdouble eyeY;
	GLdouble eyeZ;
	GLdouble centerX;
	GLdouble centerY;
	GLdouble centerZ;
	GLdouble upX;
	GLdouble upY;
	GLdouble upZ;

	tmp     = (NODE*) get_actual_argument(0, FALSE, FALSE);
	eyeX    = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(1, FALSE, FALSE);
	eyeY    = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(2, FALSE, FALSE);
	eyeZ    = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(3, FALSE, FALSE);
	centerX = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(4, FALSE, FALSE);
	centerY = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(5, FALSE, FALSE);
	centerZ = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(6, FALSE, FALSE);
	upX     = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(7, FALSE, FALSE);
	upY     = (GLdouble) (force_number(tmp));

	tmp     = (NODE*) get_actual_argument(8, FALSE, FALSE);
	upZ     = (GLdouble) (force_number(tmp));

	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	//?glMatrixMode( GL_MODELVIEW );
	//?glLoadIdentity();
	return make_number((AWKNUM) 0);
}
