/*
 * bitmap.c
 */

#include "awkgl.h"

NODE *do_RasterPos(int);
NODE *do_PixelZoom(int);
NODE *do_DrawPixels(int);
static GLenum draw_pixels_format(const char *);
static GLenum draw_pixels_type(const char *);
NODE *do_WindowPos(int);

NODE *
do_RasterPos(int nargs)
{
	NODE *tmp;
	int i;
	int arg_num = get_curfunc_arg_count();
	GLdouble arg[4]; /* x, y, z, w */

	for (i = 0; i < arg_num; i++) {
		tmp = get_scalar_argument(0 + i, FALSE);
		arg[i] = (GLdouble) force_number(tmp);
	}

	switch (arg_num) {
	case 2:
		glRasterPos2dv(arg);
		break;
	case 3:
		glRasterPos3dv(arg);
		break;
	case 4:
		glRasterPos4dv(arg);
		break;
	}
	return make_number((AWKNUM) 0);
}

NODE *
do_PixelZoom(int nargs)
{
	NODE *tmp;
	GLfloat xfactor;
	GLfloat yfactor;

	tmp = (NODE *) get_scalar_argument(0, FALSE);
	xfactor = (GLfloat) force_number(tmp);

	tmp = (NODE *) get_scalar_argument(1, FALSE);
	yfactor = (GLfloat) force_number(tmp);

	glPixelZoom(xfactor, yfactor);
	return make_number((AWKNUM) 0);
}

NODE *
do_DrawPixels(int nargs)
{
	NODE *tmp;
	int width, height;
	GLenum format, type;
	GLvoid *pixels;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	width  = (int) force_number(tmp);

	tmp    = (NODE*) get_actual_argument(1, FALSE, FALSE);
	height = (int) force_number(tmp);

	tmp    = (NODE*) get_actual_argument(2, FALSE, FALSE);
	force_string(tmp);
	format = draw_pixels_format(tmp->stptr);

	tmp    = (NODE*) get_actual_argument(3, FALSE, FALSE);
	force_string(tmp);
	type = draw_pixels_type(tmp->stptr);

	tmp    = (NODE*) get_actual_argument(4, FALSE, FALSE);
	force_string(tmp);
	pixels = NULL; //get_draw_pixels(tmp->stptr);

	glDrawPixels(width, height, format, type, pixels);
	return make_number((AWKNUM) 0);
}

static GLenum
draw_pixels_format(const char *str)
{
	GLenum format;

	if (!strcmp(str, "COLOR_INDEX")) {
		format = GL_COLOR_INDEX;	//単一の値で構成されるカラー指標
	} else if (!strcmp(str, "STENCIL_INDEX")) {
		format = GL_STENCIL_INDEX;	//単一の値で構成されるステンシル指標
	} else if (!strcmp(str, "DEPTH_COMPONENT")) {
		format = GL_DEPTH_COMPONENT;	//単一の値で構成されるデプス
	} else if (!strcmp(str, "RGBA")) {
		format = GL_RGBA;		//赤、緑、青、アルファの順で構成されるカラー
	} else if (!strcmp(str, "RED")) {
		format = GL_RED;		//単一の値で構成される赤要素
	} else if (!strcmp(str, "GREEN")) {
		format = GL_GREEN;		//単一の値で構成される緑要素
	} else if (!strcmp(str, "BLUE")) {
		format = GL_BLUE;		//単一の値で構成される青要素
	} else if (!strcmp(str, "ALPHA")) {
		format = GL_ALPHA;		//単一の値で構成されるアルファ要素
	} else if (!strcmp(str, "RGB")) {
		format = GL_RGB;		//赤、緑、青の順で構成されるカラー
	} else if (!strcmp(str, "LUMINANCE")) {
		format = GL_LUMINANCE;		//単一の値で構成される輝度
	} else if (!strcmp(str, "LUMINANCE_ALPHA")) {
		format = GL_LUMINANCE_ALPHA;	//輝度、アルファの順で構成されるカラー
	} else if (!strcmp(str, "BGR_EXT")) {
		format = GL_BGR_EXT;		//青、緑、赤の順で構成されるカラー
	} else if (!strcmp(str, "BGRA_EXT")) {
		format = GL_BGRA_EXT;		//青、緑、赤、アルファの順で構成されるカラー
	}

	return format;
}

/*
 * type には色の要素を表しているデータ型を指定します
 * 多くの場合は符号なしバイトだと思われますが、32 ビットごとに保存することもできます
 * この引数には、次のいずれかを指定することができます
 */
static GLenum
draw_pixels_type(const char *str)
{
	GLenum type;

	if (!strcmp(str, "UNSIGNED_BYTE")) {
		type = GL_UNSIGNED_BYTE;	// 符号なし 8 ビット整数
	} else if (!strcmp(str, "BYTE")) {
		type = GL_BYTE;			// 符号付き 8 ビット整数
	} else if (!strcmp(str, "BITMAP")) {
		type = GL_BITMAP;		// glBitmap() と同じビットごとの符号なし 8 ビット整数
	} else if (!strcmp(str, "UNSIGNED_SHORT")) {
		type = GL_UNSIGNED_SHORT;	// 符号なし 16 ビット整数
	} else if (!strcmp(str, "SHORT")) {
		type = GL_SHORT;		// 符号付き 16 ビット整数
	} else if (!strcmp(str, "UNSIGNED_INT")) {
		type = GL_UNSIGNED_INT;		// 符号なし 32 ビット整数
	} else if (!strcmp(str, "INT")) {
		type = GL_INT;			// 符号付き 32 ビット整数
	} else if (!strcmp(str, "FLOAT")) {
		type = GL_FLOAT;		// 単精度浮動小数点
	}

	return type;
}

NODE *
do_WindowPos(int nargs)
{
	NODE *tmp;
	int i;
	int arg_num = get_curfunc_arg_count();
	GLdouble v[3]; /* x, y, z */

	for (i = 0; i < arg_num; i++) {
		tmp = get_scalar_argument(0 + i, FALSE);
		v[i] = (GLdouble) force_number(tmp);
	}

	switch (arg_num) {
	case 2:
		glWindowPos2dv(v);
		break;
	case 3:
		glWindowPos3dv(v);
		break;
	}
	return make_number((AWKNUM) 0);
}
