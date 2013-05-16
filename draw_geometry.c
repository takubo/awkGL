/*
 * draw_geometry.c
 */

#include "awkgl.h"

NODE *do_SolidSphere(int);
NODE *do_WireSphere(int);
NODE *do_SolidCone(int);
NODE *do_WireCone(int);
NODE *do_SolidCylinder(int);
NODE *do_WireCylinder(int);
NODE *do_SolidTorus(int);
NODE *do_WireTorus(int);
NODE *do_SolidCube(int);
NODE *do_WireCube(int);
NODE *do_SolidTetrahedron(int);
NODE *do_WireTetrahedron(int);
NODE *do_SolidOctahedron(int);
NODE *do_WireOctahedron(int);
NODE *do_SolidDodecahedron(int);
NODE *do_WireDodecahedron(int);
NODE *do_SolidIcosahedron(int);
NODE *do_WireIcosahedron(int);
NODE *do_SolidTeapot(int);
NODE *do_WireTeapot(int);

//NODE *do_Point(int);
//NODE *do_Line(int);
NODE *do_DrawCircle(int nargs);
NODE *do_DrawAxes(int);
//NODE *do_DrawSolidFace(int);
//NODE *do_DrawWireFace(int);


// 各立体
//
//	球
//		radius     球の半径．
//		slices     Z軸まわりの分割数（経線に類似している）.
//		stacks     Z軸に沿った分割数（緯線に類似している）．
//
//	円錐
//		base        円錐の底辺の半径．
//		height      円錐の高さ．
//		slices      Z軸回りの分割数．
//		stacks      Z軸に沿った分割数．
//
//	円柱
//		base        円柱の底辺の半径．
//		height      円柱の高さ．
//		slices      Z軸回りの分割数．
//		stacks      Z軸に沿った分割数．
//
//	トーラス（ドーナツ）
//		innerRadius   トーラスの内径．
//		outerRadius   トーラスの外径．
//		nsides        各断面部分の分割数．
//		rings         トーラスの，管に沿った分割数．
//
//	正6面体(立法体)
//		サイズ
//
//	正4面体
//
//	正8面体
//
//	正12面体
//
//	正20面体
//
//	急須
//		サイズ
//

// 球

NODE *
do_SolidSphere(int nargs)
{
	NODE *tmp;
	GLdouble radius;
	GLint slices;
	GLint stacks;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	radius = (GLdouble) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(1, FALSE, FALSE);
	slices = (GLint) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(2, FALSE, FALSE);
	stacks = (GLint) force_number(tmp);

	glutSolidSphere(radius, slices, stacks);
	return make_number((AWKNUM) 0);
}

NODE *
do_WireSphere(int nargs)
{
	NODE *tmp;
	GLdouble radius;
	GLint slices;
	GLint stacks;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	radius = (GLdouble) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(1, FALSE, FALSE);
	slices = (GLint) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(2, FALSE, FALSE);
	stacks = (GLint) force_number(tmp);

	glutWireSphere(radius, slices, stacks);
	return make_number((AWKNUM) 0);
}

// 円錐

NODE *
do_SolidCone(int nargs)
{
	NODE *tmp;
	GLdouble base;
	GLdouble height;
	GLint slices;
	GLint stacks;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	base   = (GLdouble) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	height = (GLdouble) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(2, FALSE, FALSE);
	slices = (GLint) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(3, FALSE, FALSE);
	stacks = (GLint) force_number(tmp);

	glutSolidCone(base, height, slices, stacks);
	return make_number((AWKNUM) 0);
}

NODE *
do_WireCone(int nargs)
{
	NODE *tmp;
	GLdouble base;
	GLdouble height;
	GLint slices;
	GLint stacks;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	base   = (GLdouble) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	height = (GLdouble) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(2, FALSE, FALSE);
	slices = (GLint) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(3, FALSE, FALSE);
	stacks = (GLint) force_number(tmp);

	glutWireCone(base, height, slices, stacks);
	return make_number((AWKNUM) 0);
}

// 円柱

NODE *
do_SolidCylinder(int nargs)
{
	NODE *tmp;
	GLdouble base;
	GLdouble height;
	GLint slices;
	GLint stacks;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	base   = (GLdouble) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	height = (GLdouble) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(2, FALSE, FALSE);
	slices = (GLint) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(3, FALSE, FALSE);
	stacks = (GLint) force_number(tmp);

#ifdef HAVE_FREEGLUT
	glutSolidCylinder(base, height, slices, stacks);
#endif
	return make_number((AWKNUM) 0);
}

NODE *
do_WireCylinder(int nargs)
{
	NODE *tmp;
	GLdouble base;
	GLdouble height;
	GLint slices;
	GLint stacks;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	base   = (GLdouble) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	height = (GLdouble) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(2, FALSE, FALSE);
	slices = (GLint) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(3, FALSE, FALSE);
	stacks = (GLint) force_number(tmp);

#ifdef HAVE_FREEGLUT
	glutWireCylinder(base, height, slices, stacks);
#endif
	return make_number((AWKNUM) 0);
}

// トーラス(ドーナツ)

NODE *
do_SolidTorus(int nargs)
{
	NODE *tmp;
	GLdouble innerRadius;
	GLdouble outerRadius;
	GLint nsides;
	GLint rings;

	tmp         = (NODE*) get_actual_argument(0, FALSE, FALSE);
	innerRadius = (GLdouble) force_number(tmp);
	tmp         = (NODE*) get_actual_argument(0, FALSE, FALSE);
	outerRadius = (GLdouble) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(2, FALSE, FALSE);
	nsides = (GLint) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(3, FALSE, FALSE);
	rings  = (GLint) force_number(tmp);

	glutSolidTorus(innerRadius, outerRadius, nsides, rings);
	return make_number((AWKNUM) 0);
}

NODE *
do_WireTorus(int nargs)
{
	NODE *tmp;
	GLdouble innerRadius;
	GLdouble outerRadius;
	GLint nsides;
	GLint rings;

	tmp         = (NODE*) get_actual_argument(0, FALSE, FALSE);
	innerRadius = (GLdouble) force_number(tmp);
	tmp         = (NODE*) get_actual_argument(0, FALSE, FALSE);
	outerRadius = (GLdouble) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(2, FALSE, FALSE);
	nsides = (GLint) force_number(tmp);
	tmp    = (NODE*) get_actual_argument(3, FALSE, FALSE);
	rings  = (GLint) force_number(tmp);

	glutWireTorus(innerRadius, outerRadius, nsides, rings);
	return make_number((AWKNUM) 0);
}

// 立方体

NODE *
do_SolidCube(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glutSolidCube(size);
	return make_number((AWKNUM) 0);
}

NODE *
do_WireCube(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glutWireCube(size);
	return make_number((AWKNUM) 0);
}

// 4面体

NODE *
do_SolidTetrahedron(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glPushMatrix();
	glScaled(size, size, size);
	glutSolidTetrahedron();
	glPopMatrix();

	return make_number((AWKNUM) 0);
}

NODE *
do_WireTetrahedron(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glPushMatrix();
	glScaled(size, size, size);
	glutWireTetrahedron();
	glPopMatrix();

	return make_number((AWKNUM) 0);
}

// 8面体

NODE *
do_SolidOctahedron(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glPushMatrix();
	glScaled(size, size, size);
	glutSolidOctahedron();
	glPopMatrix();

	return make_number((AWKNUM) 0);
}

NODE *
do_WireOctahedron(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glPushMatrix();
	glScaled(size, size, size);
	glutWireOctahedron();
	glPopMatrix();

	return make_number((AWKNUM) 0);
}

// 12面体

NODE *
do_SolidDodecahedron(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glPushMatrix();
	glScaled(size, size, size);
	glutSolidDodecahedron();
	glPopMatrix();

	return make_number((AWKNUM) 0);
}

NODE *
do_WireDodecahedron(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glPushMatrix();
	glScaled(size, size, size);
	glutWireDodecahedron();
	glPopMatrix();

	return make_number((AWKNUM) 0);
}

// 20面体

NODE *
do_SolidIcosahedron(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glPushMatrix();
	glScaled(size, size, size);
	glutSolidIcosahedron();
	glPopMatrix();

	return make_number((AWKNUM) 0);
}

NODE *
do_WireIcosahedron(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glPushMatrix();
	glScaled(size, size, size);
	glutWireIcosahedron();
	glPopMatrix();

	return make_number((AWKNUM) 0);
}

// ティーポット

NODE *
do_SolidTeapot(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glutSolidTeapot(size);
	return make_number((AWKNUM) 0);
}

NODE *
do_WireTeapot(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glutWireTeapot(size);
	return make_number((AWKNUM) 0);
}

#if 0
NODE *
do_Point(int nargs)
{
	glColor3d(1.0, 0.0, 0.0); // 赤
	glVertex2d(-0.5, -0.5);
	glColor3d(0.0, 1.0, 0.0); // 緑
	glVertex2d(0.5, -0.5);
	glColor3d(0.0, 0.0, 1.0); // 青
	glVertex2d(0.5, 0.5);
	glColor3d(1.0, 1.0, 0.0); // 黄
	glVertex2d(-0.5, 0.5);
	return make_number((AWKNUM) 0);
}
#endif

// 円
NODE *
do_DrawCircle(int nargs)
{
	NODE *tmp;
	GLdouble radius;
	GLint slices;
	int fill;
	int i;
	GLdouble a;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	radius = (GLdouble) force_number(tmp);

	tmp    = (NODE*) get_actual_argument(1, FALSE, FALSE);
	slices = (GLint) force_number(tmp);

	tmp    = (NODE*) get_actual_argument(2, FALSE, FALSE);
	fill   = (int) force_number(tmp);

	a = (2 * M_PI) / slices;

	if (fill) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex2d(0, 0);
	} else {
		glBegin(GL_LINE_LOOP);
	}
	/* CCW is FONT */
	for (i = slices; i >= 0; i--) {
		glVertex2d(radius * cos(i * a), radius * sin(i * a));
	}
	glEnd();

	return make_number((AWKNUM) 0);
}

NODE *
do_DrawAxes(int nargs)
{
	NODE *tmp;
	GLboolean lighting;
	GLdouble len;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	len = (GLdouble) force_number(tmp);

	if (glIsEnabled(GL_LIGHTING)) {
	    lighting = GL_TRUE;
	    glDisable(GL_LIGHTING);
	} else {
	    lighting = GL_FALSE;
	}

	glBegin(GL_LINES);
	glColor3d(1,0,0);	// X axis is red.
	glVertex3d(0, 0, 0);
	glVertex3d(len, 0, 0);
	glColor3d(0,1,0);	// Y axis is green.
	glVertex3d(0, 0, 0);
	glVertex3d(0, len, 0);
	glColor3d(0,0,1);	// Z axis is blue.
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, len);
	glEnd();

	if (lighting) {
	    glEnable(GL_LIGHTING);
	}

	return make_number((AWKNUM) 0);
}
