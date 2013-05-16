/*
 * font.c
 */

#include "awkgl.h"

NODE *do_BitmapCharacter(int);
NODE *do_BitmapWidth(int);
NODE *do_BitmapLength(int);
#if FREEGLUT
NODE *do_BitmapHeight(int);
NODE *do_BitmapString(int);
#endif

NODE *do_StrokeCharacter(int);
NODE *do_StrokeWidth(int);
NODE *do_StrokeLength(int);
#if FREEGLUT
NODE *do_StrokeHeight(int);
NODE *do_StrokeString(int);
#endif

static void *str2font(const char *str);

NODE *
do_BitmapCharacter(int nargs)
{
	NODE *tmp;
	void *font;
	int character;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);
	if ((font = str2font(tmp->stptr)) == NULL) {
		// TODO		errror
	}

	tmp = (NODE *) get_scalar_argument(1, FALSE);
	force_string(tmp);
	if (tmp->stlen != 1) {
		// TODO		errror
	}
	character = (int) tmp->stptr[0];

	glutBitmapCharacter(font, character);
	return make_number((AWKNUM) 0);
}

NODE *
do_BitmapWidth(int nargs)
{
	NODE *tmp;
	void *font;
	int character;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);
	if ((font = str2font(tmp->stptr)) == NULL) {
		// TODO
	}

	tmp = (NODE *) get_scalar_argument(1, FALSE);
	force_string(tmp);
	if (tmp->stlen != 1) {
		// TODO
	}
	character = (int) tmp->stptr[0];

	return make_number((AWKNUM) glutBitmapWidth(font, character));
}

NODE *
do_BitmapLength(int nargs)
{
	NODE *tmp;
	void *font;
	const unsigned char *string;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);
	if ((font = str2font(tmp->stptr)) == NULL) {
		// TODO
	}

	tmp = (NODE *) get_scalar_argument(1, FALSE);
	force_string(tmp);
	string = (const unsigned char *) tmp->stptr;	//TODO cast

	return make_number((AWKNUM) glutBitmapLength(font, string));
}

#if FREEGLUT
NODE *
do_BitmapHeight(int nargs)
{
	NODE *tmp;
	void *font;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);
	if ((font = str2font(tmp->stptr)) == NULL) {
		// TODO
	}

	return make_number((AWKNUM) glutBitmapHeight(font));
}

NODE *
do_BitmapString(int nargs)
{
	NODE *tmp;
	void *font;
	const unsigned char *string;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);
	if ((font = str2font(tmp->stptr)) == NULL) {
		// TODO
	}

	tmp = (NODE *) get_scalar_argument(1, FALSE);
	force_string(tmp);
	string = (const unsigned char *) tmp->stptr;	//TODO cast

	glutBitmapString(font, string);
	return make_number((AWKNUM) 0);
}
#endif /* FREEGLUT */

NODE *
do_StrokeCharacter(int nargs)
{
	NODE *tmp;
	void *font;
	int character;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);
	if ((font = str2font(tmp->stptr)) == NULL) {
		// TODO
	}

	tmp = (NODE *) get_scalar_argument(1, FALSE);
	force_string(tmp);
	if (tmp->stlen != 1) {
		// TODO
	}
	character = (int) tmp->stptr[0];

	glutStrokeCharacter(font, character);
	return make_number((AWKNUM) 0);
}

NODE *
do_StrokeWidth(int nargs)
{
	NODE *tmp;
	void *font;
	int character;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);
	if ((font = str2font(tmp->stptr)) == NULL) {
		// TODO
	}

	tmp = (NODE *) get_scalar_argument(1, FALSE);
	force_string(tmp);
	if (tmp->stlen != 1) {
		// TODO
	}
	character = (int) tmp->stptr[0];

	return make_number((AWKNUM) glutStrokeWidth(font, character));
}

NODE *
do_StrokeLength(int nargs)
{
	NODE *tmp;
	void *font;
	const unsigned char *string;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);
	if ((font = str2font(tmp->stptr)) == NULL) {
		// TODO
	}

	tmp = (NODE *) get_scalar_argument(1, FALSE);
	force_string(tmp);
	string = (const unsigned char *) tmp->stptr;

	return make_number((AWKNUM) glutStrokeLength(font, string));
}

#if FREEGLUT
NODE *
do_StrokeHeight(int nargs)
{
	NODE *tmp;
	void *font;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);
	if ((font = str2font(tmp->stptr)) == NULL) {
		// TODO
	}

	return make_number((AWKNUM) glutStrokeHeight(font));
}

NODE *
do_StrokeString(int nargs)
{
	NODE *tmp;
	void *font;
	const unsigned char *string;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	force_string(tmp);
	if ((font = str2font(tmp->stptr)) == NULL) {
		// TODO
	}

	tmp = (NODE *) get_scalar_argument(1, FALSE);
	force_string(tmp);
	string = (const unsigned char *) tmp->stptr;

	glutStrokeString(font, string);
	return make_number((AWKNUM) 0);
}
#endif /* FREEGLUT */

static void *
str2font(const char *str)
{
	void *font;

	if (!strncmp(str, "GLUT_", 5))
		str += 5;

	if (!strcmp(str, "STROKE_ROMAN")) {
		font = GLUT_STROKE_ROMAN;
	} else if (!strcmp(str, "STROKE_MONO_ROMAN")) {
		font = GLUT_STROKE_MONO_ROMAN;
	} else if (!strcmp(str, "BITMAP_9_BY_15")) {
		font = GLUT_BITMAP_9_BY_15;
	} else if (!strcmp(str, "BITMAP_8_BY_13")) {
		font = GLUT_BITMAP_8_BY_13;
	} else if (!strcmp(str, "BITMAP_TIMES_ROMAN_10")) {
		font = GLUT_BITMAP_TIMES_ROMAN_10;
	} else if (!strcmp(str, "BITMAP_TIMES_ROMAN_24")) {
		font = GLUT_BITMAP_TIMES_ROMAN_24;
	} else if (!strcmp(str, "BITMAP_HELVETICA_10")) {
		font = GLUT_BITMAP_HELVETICA_10;
	} else if (!strcmp(str, "BITMAP_HELVETICA_12")) {
		font = GLUT_BITMAP_HELVETICA_12;
	} else if (!strcmp(str, "BITMAP_HELVETICA_18")) {
		font = GLUT_BITMAP_HELVETICA_18;
	} else {
		font = NULL;
	}

	return font;
}
