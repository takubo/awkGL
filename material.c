/*
 * material.c
 */

#include "awkgl.h"

NODE *do_ClearColor(int);

NODE *do_Color(int);

NODE *do_Light(int);
GLenum light_light_s(const char *);
static GLenum light_light_n(int);
static GLenum light_pname(const char *);

NODE *do_Normal(int);

NODE *do_Material(int);
GLenum material_face(const char *);
static GLenum material_pname(const char *);

NODE *
do_ClearColor(int nargs)
{
	NODE *tmp;
	GLclampf red, green, blue;

	tmp   = (NODE*) get_actual_argument(0, FALSE, FALSE);
	red   = (GLclampf) (force_number(tmp) / 255);

	tmp   = (NODE*) get_actual_argument(1, FALSE, FALSE);
	green = (GLclampf) (force_number(tmp) / 255);

	tmp   = (NODE*) get_actual_argument(2, FALSE, FALSE);
	blue  = (GLclampf) (force_number(tmp) / 255);

	//printf("Red = %d;   Green = %d;   Blue = %d;\n",
	//	(int)(red * 255), (int)(green * 255), (int)(blue * 255));

	glClearColor(red, green, blue, 1.0);
	return make_number((AWKNUM) 0);
}

NODE *
do_Color(int nargs)
{
	NODE *tmp;
	GLdouble red, green, blue;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	red    = (GLdouble) (force_number(tmp) / 255);
	tmp    = (NODE*) get_actual_argument(1, FALSE, FALSE);
	green  = (GLdouble) (force_number(tmp) / 255);
	tmp    = (NODE*) get_actual_argument(2, FALSE, FALSE);
	blue   = (GLdouble) (force_number(tmp) / 255);

	glColor3d(red, green, blue);
	return make_number((AWKNUM) 0);
}

// 光源
NODE *
do_Light(int nargs)
{
	NODE *tmp;
	GLenum light;
	GLenum pname;
	float params[4];
	int param_num;
	int i;

	//tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	//force_string(tmp);
	//light = light_light_s(tmp->stptr);

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	light = light_light_n((int) force_number(tmp));

	tmp = (NODE*) get_actual_argument(1, FALSE, FALSE);
	force_string(tmp);
	pname = light_pname(tmp->stptr);

	switch (pname) {
		case GL_AMBIENT:
		case GL_DIFFUSE:
		case GL_SPECULAR:
		case GL_POSITION:
			param_num = 4;
			break;
		case GL_SPOT_DIRECTION:
			param_num = 3;
			break;
		default:
			param_num = 1;
			break;
	}

	for (i = 0; i < param_num; i++) {
		tmp = (NODE*) get_actual_argument(i + 2, FALSE, FALSE);
		params[i] = (GLfloat) force_number(tmp);
	}

	// void glLightfv( GLenum light , GLenum pname , const GLfloat *params );
	glLightfv(light, pname , params);
	return make_number((AWKNUM) 0);
}

GLenum
light_light_s(const char *str)
{
	GLenum light;

	if (!strcmp(str, "LIGHT0")) {
		light = GL_LIGHT0;
	} else if (!strcmp(str, "LIGHT1")) {
		light = GL_LIGHT1;
	} else if (!strcmp(str, "LIGHT2")) {
		light = GL_LIGHT2;
	} else if (!strcmp(str, "LIGHT3")) {
		light = GL_LIGHT3;
	} else if (!strcmp(str, "LIGHT4")) {
		light = GL_LIGHT4;
	} else if (!strcmp(str, "LIGHT5")) {
		light = GL_LIGHT5;
	} else if (!strcmp(str, "LIGHT6")) {
		light = GL_LIGHT6;
	} else if (!strcmp(str, "LIGHT7")) {
		light = GL_LIGHT7;
	}

	return light;
}

static GLenum
light_light_n(int num)
{
	GLenum light;

	switch (num) {
		case 0:
			light = GL_LIGHT0;
			break;
		case 1:
			light = GL_LIGHT1;
			break;
		case 2:
			light = GL_LIGHT2;
			break;
		case 3:
			light = GL_LIGHT3;
			break;
		case 4:
			light = GL_LIGHT4;
			break;
		case 5:
			light = GL_LIGHT5;
			break;
		case 6:
			light = GL_LIGHT6;
			break;
		case 7:
			light = GL_LIGHT7;
			break;
		default:
			light = num; /* TODO */
			break;
	}

	return light;
}

// GL_AMBIENT
// 	環境光を4つの整数値、または浮動小数点値で指定します
//	初期値は (0 , 0 , 0 , 1)
// GL_DIFFUSE
// 	拡散光を4つの整数値、または浮動小数点値で指定します
//	初期値は GL_LIGHT0 が(1 , 1 , 1 , 1)、それ以外は (0 , 0 , 0, 0)
// GL_SPECULAR
// 	鏡面光を4つの整数値、または浮動小数点値で指定します
//	初期値は GL_LIGHT0 が(1 , 1 , 1 , 1)、それ以外は (0 , 0 , 0, 0)
// GL_POSITION
// 	照明の位置を4つの整数値、または浮動小数点値で指定します
//	初期値は (0 , 0 , 1 , 0)
// GL_SPOT_DIRECTION
// 	照明の方向を3つの整数値、または浮動小数点値で指定します
//	初期値は (0 , 0 , -1)
// GL_SPOT_EXPONENT
// 	輝度の分布を単独の整数値、または浮動小数点値で指定します
//	初期値は 0
// GL_SPOT_CUTOFF
// 	最大放射角度を単独の整数値、または浮動小数点値で指定します
//	範囲は 0 ～ 90 までと、特別値の 180 のみが有効です
//	初期値は 180
// GL_CONSTANT_ATTENUATION
// 	一定減衰の率を単独の整数値、または浮動小数点値で指定します
//	初期値は 1
// GL_LINEAR_ATTENUATION
// 	線形減衰の率を単独の整数値、または浮動小数点値で指定します
//	初期値は 0
// GL_QUADRATIC_ATTENUATION
// 	2次減衰の率を単独の整数値、または浮動小数点値で指定します
//	初期値は 0
static GLenum
light_pname(const char *str)
{
	GLenum pname;

	if (!strcmp(str, "AMBIENT")) {
		pname = GL_AMBIENT;
	} else if (!strcmp(str, "DIFFUSE")) {
		pname = GL_DIFFUSE;
	} else if (!strcmp(str, "SPECULAR")) {
		pname = GL_SPECULAR;
	} else if (!strcmp(str, "POSITION")) {
		pname = GL_POSITION;
	} else if (!strcmp(str, "DIRECTION")) {
		pname = GL_SPOT_DIRECTION;
	} else if (!strcmp(str, "EXPONENT")) {
		pname = GL_SPOT_EXPONENT;
	} else if (!strcmp(str, "CUTOFF")) {
		pname = GL_SPOT_CUTOFF;
	} else if (!strcmp(str, "LINEAR_ATTENUATION")) {
		pname = GL_LINEAR_ATTENUATION;
	} else {
		fatal(_("Invalid light param name"));
		pname = 0; /* suppress warning */
	}

	return pname;
}

// 法線ベクトル
NODE *
do_Normal(int nargs)
{
	NODE *tmp;
	GLdouble nx;
	GLdouble ny;
	GLdouble nz;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	nx  = (GLdouble) force_number(tmp);
	tmp = (NODE*) get_actual_argument(1, FALSE, FALSE);
	ny  = (GLdouble) force_number(tmp);
	tmp = (NODE*) get_actual_argument(2, FALSE, FALSE);
	nz  = (GLdouble) force_number(tmp);

	glNormal3d(nx, ny, nz);
	return make_number((AWKNUM) 0);
}

// 材質
NODE *
do_Material(int nargs)
{
	NODE *tmp;
	GLenum face;
	GLenum pname;
	float params[8];
	int param_num;
	int i;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);
	face = material_face(tmp->stptr);

	tmp = (NODE*) get_actual_argument(1, FALSE, FALSE);
	force_string(tmp);
	pname = material_pname(tmp->stptr);

	switch (pname) {
		case GL_SHININESS:
			param_num = 1;
			break;
		case GL_COLOR_INDEXES:
			param_num = 3;
			break;
		case GL_AMBIENT_AND_DIFFUSE:
			param_num = 8;
			break;
		default:
			param_num = 4;
			break;
	}

	for (i = 0; i < param_num; i++) {
		tmp = (NODE*) get_actual_argument(i + 2, FALSE, FALSE);
		params[i] = (GLfloat) force_number(tmp);
	}

	// OpenGLで質感を設定するときは、通常glMaterialfv()を使います。
	// いままで使ってきた、glColor3fv()と同様に、図形を描く前に質感を設定するという手順をとります。
	// OpenGLのポリゴンには、表と裏という概念があって、faceはそのどちらの面の質感を設定するかを指定する。
	// GL_FRONT(表)、GL_BACK(裏)、GL_FRONT_AND_BACK(両方)のうちのいずれか。
	// 今回は、ひとまずGL_FRONT_AND_BACKを指定しておいた。
	// ポリゴンの表裏に関しては、他の機会に説明する。
	// pnameは、質感のどのパラメタを設定するかを指定する。
	// GL_AMBIENT、GL_DIFFUSE、GL_SPECULAR、GL_EMISSION、GL_SHININESSなどがあり、このうちの１つを選んで設定する。
	// それぞれ、質感についてで解説した通り。
	// paramsには、実際に設定する値の入った配列を渡す。
	// GL_AMBIENT、GL_DIFFUSE、GL_SPECULAR、GL_EMISSIONの場合は、RGBA形式である。
	// それぞれ、─１から１の範囲の値を入れる。
	// GL_SHININESSの場合は、渡す値は１つで、０から１２８の範囲の値である。
	// GL_SHINESSを設定するだけなら、glMaterialf()を使うこともできる。
	//
	//void glMaterialfv(GLenum face, GLenum pname, const GLfloat *params)

	glMaterialfv(face, pname, params);
	return make_number((AWKNUM) 0);
}

GLenum
material_face(const char *str)
{
	GLenum face;

	if (!strcmp(str, "FRONT")) {
		face = GL_FRONT;
	} else if (!strcmp(str, "BACK")) {
		face = GL_BACK;
	} else if (!strcmp(str, "FRONT_AND_BACK")) {
		face = GL_FRONT_AND_BACK;
	} else if (!strcmp(str, "BOTH")) {
		face = GL_FRONT_AND_BACK;
	} else {
		fatal(_("Invalid material face"));
		face = 0; /* suppress warning */
	}

	return face;
}

// GL_AMBIENT
// 	環境光を4つの整数値、または浮動小数点値で指定します
// 	初期値は (0.2 , 0.2 , 0.2 , 1)
// GL_DIFFUSE
// 	拡散光を4つの整数値、または浮動小数点値で指定します
// 	初期値は GL_LIGHT0 が(0.8 , 0.8 , 0.8 , 1)、それ以外は (0 , 0 , 0, 0)
// GL_SPECULAR
// 	鏡面光を4つの整数値、または浮動小数点値で指定します
// 	初期値は (0 , 0 , 0, 1)
// GL_EMISSION
// 	放射輝度を4つの整数値、または浮動小数点値で指定します
// 	初期値は (0 , 0 , 0 , 1)
// GL_SHININESS
// 	鏡面光の指数を単一の整数値、または浮動小数点値で指定します
// 	範囲は 0 ～ 128 まで、初期値は 0 です
// GL_AMBIENT_AND_DIFFUSE
// 	環境光と拡散光を同時に指定します
// GL_COLOR_INDEXES
// 	環境光、拡散光、鏡面光のカラー指標を
// 	3つの整数値、または浮動小数点値で指定します
static GLenum
material_pname(const char *str)
{
	GLenum pname;

	if (!strcmp(str, "AMBIENT")) {
		pname = GL_AMBIENT;
	} else if (!strcmp(str, "DIFFUSE")) {
		pname = GL_DIFFUSE;
	} else if (!strcmp(str, "SPECULAR")) {
		pname = GL_SPECULAR;
	} else if (!strcmp(str, "EMISSION")) {
		pname = GL_EMISSION;
	} else if (!strcmp(str, "SHININESS")) {
		pname = GL_SHININESS;
	} else if (!strcmp(str, "AMBIENT_AND_DIFFUSE")) {
		pname = GL_AMBIENT_AND_DIFFUSE;
	} else if (!strcmp(str, "COLOR_INDEXES")) {
		pname = GL_COLOR_INDEXES;
	} else {
		fatal(_("Invalid material name"));
		pname = 0; /* suppress warning */
	}

	return pname;
}
