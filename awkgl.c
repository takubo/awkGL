#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include "awk.h"

int plugin_is_GPL_compatible;

NODE *Reshape_user_func = NULL;
NODE *Keyboard_user_func = NULL;
NODE *KeyboardUp_user_func = NULL;
NODE *Special_user_func = NULL;
NODE *SpecialUp_user_func = NULL;
NODE *Mouse_user_func = NULL;
NODE *Motion_user_func = NULL;
NODE *PassiveMotion_user_func = NULL;
NODE *Entry_user_func = NULL;
NODE *Display_user_func = NULL;
NODE *Idle_user_func = NULL;
NODE *Timer_user_func = NULL;

static void set_default_user_func(void);
//?static NODE* do_GameMode(int);
static NODE* do_ReshapeFunc(int);
static NODE* do_Viewport(int);
static NODE* do_SetWindowPosSize(int);	// Only awkGL
static NODE* do_SetWindowTitle(int);
static NODE* do_SetIconTitle(int);
static NODE* do_ReshapeWindow(int);
static NODE* do_PositionWindow(int);
static NODE* do_ShowWindow(int);
static NODE* do_HideWindow(int);
static NODE* do_IconifyWindow(int);
static NODE* do_PushWindow(int);
static NODE* do_PopWindow(int);
static NODE* do_FullScreen(int);
static NODE* do_ClearColor(int);
static NODE* do_CreateWindow(int);
static NODE* do_KeyboardFunc(int);
static NODE* do_KeyboardUpFunc(int);
static NODE* do_SpecialFunc(int);
static NODE* do_SpecialUpFunc(int);
static NODE* do_MouseFunc(int);
static NODE* do_MotionFunc(int);
static NODE* do_PassiveMotionFunc(int);
static NODE* do_GetModifiers(int);
static NODE* do_EntryFunc(int);
static NODE* do_DisplayFunc(int);
static NODE *do_TimerFunc(int);
static NODE* do_MainLoop(int);
static NODE* do_PostRedisplay(int);	//?
static NODE* do_SwapBuffers(int);	//?
static NODE* do_Enable(int);
static NODE* do_Disable(int);
GLenum enable_disable(const char *);
static void AgReshape(int, int);
static void AgKeyboard(unsigned char, int, int);
static void AgKeyboardUp(unsigned char, int, int);
static void AgSpecial(int, int, int);
static void AgSpecialUp(int, int, int);
static const char* specialkey2str(int);
static void AgMouse(int, int, int, int);
static void AgMotion(int, int);
static void AgPassiveMotion(int, int);
static void AgEntry(int);
static void AgDisplay(void);
static void AgTimer(int);
static AWKNUM callback_user_func(NODE *, NODE *[], int);
static NODE* user_func(void);
static NODE* user_func_sub(const char *);
void resize(int, int);
static NODE* do_Begin(int);
static NODE* do_End(int);
static NODE* do_Color(int);
static NODE* do_Vertex2d(int);
static NODE* do_Vertex3d(int);
static NODE* do_Ortho(int);
static NODE* do_Frustum(int);
static NODE* do_Perspective(int);
static NODE* do_Lookat(int);

static NODE* do_LoadIdentity(int);
static NODE* do_PushMatrix(int);
static NODE* do_PopMatrix(int);

static NODE* do_Rotate(int);
static NODE* do_Transrate(int);
static NODE* do_Scale(int);

static NODE* do_DrawPixels(int);
static GLenum draw_pixels_format(const char*);
static GLenum draw_pixels_type(const char*);

static NODE* do_Light(int);
static GLenum light_light_s(const char*);
static GLenum light_light_n(int);
static GLenum light_pname(const char*);
static NODE* do_Normal(int);
static NODE* do_Material(int);
static GLenum material_face(const char*);
static GLenum material_pname(const char*);

static NODE* do_PointSize(int);
static NODE* do_LineWidth(int);
static NODE* do_PolygonMode(int);
static GLenum polygon_mode(const char*);
static NODE* do_LineStipple(int);

static NODE* do_SolidSphere(int);
static NODE* do_WireSphere(int);
static NODE* do_SolidCone(int);
static NODE* do_WireCone(int);
static NODE* do_SolidCylinder(int);
static NODE* do_WireCylinder(int);
static NODE* do_SolidTorus(int);
static NODE* do_WireTorus(int);
static NODE* do_SolidCube(int);
static NODE* do_WireCube(int);
static NODE* do_SolidTetrahedron(int);
static NODE* do_WireTetrahedron(int);
static NODE* do_SolidOctahedron(int);
static NODE* do_WireOctahedron(int);
static NODE* do_SolidDodecahedron(int);
static NODE* do_WireDodecahedron(int);
static NODE* do_SolidIcosahedron(int);
static NODE* do_WireIcosahedron(int);
static NODE* do_SolidTeapot(int);
static NODE* do_WireTeapot(int);

//static NODE* do_Point(int);		//??
//static NODE* do_Line(int);		//??
static NODE * do_DrawCircle(int nargs);
static NODE * do_DrawAxes(int);
//static NODE* do_DrawSolidFace(int)	//??
//static NODE* do_DrawWireFace(int);	//??

static NODE* do_pi(int);
static NODE* do_d2r(int);
static NODE* do_r2d(int);


NODE *
dlload(NODE *tree, void *dl)
{
	make_builtin("ReshapeFunc", do_ReshapeFunc, 4);
	make_builtin("Viewport", do_Viewport, 4);
	make_builtin("SetWindowPosSize", do_SetWindowPosSize, 4);
	make_builtin("SetWindowTitle", do_SetWindowTitle, 1);
	make_builtin("SetIconTitle", do_SetIconTitle, 1);
	make_builtin("ReshapeWindow", do_ReshapeWindow, 2);
	make_builtin("positionWindow", do_PositionWindow, 2);
	make_builtin("ShowWindow", do_ShowWindow, 0);
	make_builtin("HideWindow", do_HideWindow, 0);
	make_builtin("IconifyWindow", do_IconifyWindow, 0);
	make_builtin("PushWindow", do_PushWindow, 0);
	make_builtin("PopWindow", do_PopWindow, 0);
	make_builtin("FullScreen", do_FullScreen, 0);
	//make_builtin("GameMode", do_GameMode, 1);
	make_builtin("CreateWindow", do_CreateWindow, 1);
	make_builtin("KeyboardFunc", do_KeyboardFunc, 1);
	make_builtin("KeyboardUpFunc", do_KeyboardUpFunc, 1);
	make_builtin("SpecialFunc", do_SpecialFunc, 1);
	make_builtin("SpecialUpFunc", do_SpecialUpFunc, 1);
	make_builtin("MouseFunc", do_MouseFunc, 1);
	make_builtin("MotionFunc", do_MotionFunc, 1);
	make_builtin("PassiveMotionFunc", do_PassiveMotionFunc, 1);
	make_builtin("GetModifiers", do_GetModifiers, 0);
	make_builtin("EntryFunc", do_EntryFunc, 1);
	make_builtin("DisplayFunc", do_DisplayFunc, 1);
	make_builtin("TimerFunc", do_TimerFunc, 3);
	make_builtin("MainLoop", do_MainLoop, 0);
	make_builtin("PostRedisplay", do_PostRedisplay, 0);
	make_builtin("glutSwapBuffers", do_SwapBuffers, 0);
	make_builtin("Enable", do_Enable, 1);
	make_builtin("Disable", do_Disable, 1);
	make_builtin("ClearColor", do_ClearColor, 3);
	make_builtin("Begin", do_Begin, 3);
	make_builtin("End", do_End, 3);
	make_builtin("Color", do_Color, 3);
	make_builtin("Vertex2d", do_Vertex2d, 2);
	make_builtin("Vertex3d", do_Vertex3d, 3);
//	make_builtin("Point", do_Point, 3);
//	make_builtin("Line", do_Line, 3);
	make_builtin("Ortho", do_Ortho, 6);
	make_builtin("Frustum", do_Frustum, 6);
	make_builtin("Perspective", do_Perspective, 4);
	make_builtin("LookAt", do_Lookat, 9);

	make_builtin("LoadIdentity", do_LoadIdentity, 1);
	make_builtin("PushMatrix", do_PushMatrix, 1);
	make_builtin("PopMatrix", do_PopMatrix, 1);

	make_builtin("Rotate", do_Rotate, 4);
	make_builtin("Translate", do_Transrate, 4);
	make_builtin("Scale", do_Scale, 4);

	make_builtin("DrawPixels", do_DrawPixels, 5);

	make_builtin("Light", do_Light, 9);
	make_builtin("Normal", do_Normal, 3);
	make_builtin("Material", do_Material, 8);

	make_builtin("PointSize", do_PointSize, 1);
	make_builtin("LineWidth", do_LineWidth, 1);
	make_builtin("PolygonMode", do_PolygonMode, 2);
	make_builtin("LineStipple", do_LineStipple, 2);

	make_builtin("SolidSphere", do_SolidSphere, 3);
	make_builtin("WireSphere", do_WireSphere, 3);
	make_builtin("SolidCone", do_SolidCone, 4);
	make_builtin("WireCone", do_WireCone, 4);
	make_builtin("SolidCylinder", do_SolidCylinder, 4);
	make_builtin("WireCylinder", do_WireCylinder, 4);
	make_builtin("SolidTorus", do_SolidTorus, 4);
	make_builtin("WireTorus", do_WireTorus, 4);
	make_builtin("SolidCube", do_SolidCube, 1);
	make_builtin("WireCube", do_WireCube, 1);
	make_builtin("SolidTetrahedron", do_SolidTetrahedron, 1);
	make_builtin("WireTetrahedron", do_WireTetrahedron, 1);
	make_builtin("SolidOctahedron", do_SolidOctahedron, 1);
	make_builtin("WireOctahedron", do_WireOctahedron, 1);
	make_builtin("SolidDodecahedron", do_SolidDodecahedron, 1);
	make_builtin("WireDodecahedron", do_WireDodecahedron, 1);
	make_builtin("SolidIcosahedron", do_SolidIcosahedron, 1);
	make_builtin("WireIcosahedron", do_WireIcosahedron, 1);
	make_builtin("SolidTeapot", do_SolidTeapot, 1);
	make_builtin("WireTeapot", do_WireTeapot, 1);

	make_builtin("DrawCircle", do_DrawCircle, 3);
	make_builtin("DrawAxes", do_DrawAxes, 1);

	make_builtin("pi", do_pi, 1);
	make_builtin("radian", do_d2r, 1);
	make_builtin("degree", do_r2d, 1);
	make_builtin("d2r", do_d2r, 1);
	make_builtin("r2d", do_r2d, 1);
	make_builtin("deg2rad", do_d2r, 1);
	make_builtin("rad2deg", do_r2d, 1);


	int argc=0; char *argv[1]; glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	return make_number((AWKNUM) 0);
}

static void
set_default_user_func()
{
	NODE *fnc_ptr;

	fnc_ptr = user_func_sub("reshape");
	if (fnc_ptr != NULL) {
		Reshape_user_func = fnc_ptr;
		glutReshapeFunc(AgReshape);
	}

	fnc_ptr = user_func_sub("display");
	if (fnc_ptr != NULL) {
		Display_user_func = fnc_ptr;
		glutDisplayFunc(AgDisplay);
	}

	fnc_ptr = user_func_sub("keyboard");
	if (fnc_ptr != NULL) {
		Keyboard_user_func = fnc_ptr;
		glutKeyboardFunc(AgKeyboard);
	}

	fnc_ptr = user_func_sub("keyboardup");
	if (fnc_ptr != NULL) {
		KeyboardUp_user_func = fnc_ptr;
		glutKeyboardUpFunc(AgKeyboardUp);
	}

	fnc_ptr = user_func_sub("special");
	if (fnc_ptr != NULL) {
		Special_user_func = fnc_ptr;
		glutSpecialFunc(AgSpecial);
	}

	fnc_ptr = user_func_sub("specialup");
	if (fnc_ptr != NULL) {
		SpecialUp_user_func = fnc_ptr;
		glutSpecialUpFunc(AgSpecialUp);
	}

	fnc_ptr = user_func_sub("mouse");
	if (fnc_ptr != NULL) {
		Mouse_user_func = fnc_ptr;
		glutMouseFunc(AgMouse);
	}

	fnc_ptr = user_func_sub("motion");
	if (fnc_ptr != NULL) {
		Motion_user_func = fnc_ptr;
		glutMotionFunc(AgMotion);
	}

	fnc_ptr = user_func_sub("entry");
	if (fnc_ptr != NULL) {
		Entry_user_func = fnc_ptr;
		glutEntryFunc(AgEntry);
	}

	return;
}

static NODE *
do_SetWindowPosSize(int nargs)
{
	NODE *tmp;
	int x, y, width, height;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	x      = (int) force_number(tmp);

	tmp    = (NODE*) get_actual_argument(1, FALSE, FALSE);
	y      = (int) force_number(tmp);

	tmp    = (NODE*) get_actual_argument(2, FALSE, FALSE);
	width  = (int) force_number(tmp);

	tmp    = (NODE*) get_actual_argument(3, FALSE, FALSE);
	height = (int) force_number(tmp);

	//printf("X = %d;   Y = %d;   Width = %d;   Height = %d\n",
	//	x, y, width, height);

	glutInitWindowPosition(x, y);
	glutInitWindowSize(width, height);
	return make_number((AWKNUM) 0);
}

static NODE *
do_SetWindowTitle(int nargs)
{
	NODE *tmp;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);

	glutSetWindowTitle(tmp->stptr);
	return make_number((AWKNUM) 0);
}

	static NODE *
do_SetIconTitle(int nargs)
{
	NODE *tmp;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);

	glutSetIconTitle(tmp->stptr);
	return make_number((AWKNUM) 0);
}

	static NODE *
do_ReshapeWindow(int nargs)
{
	NODE *tmp;
	int width, height;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	width  = (int) force_number(tmp);

	tmp    = (NODE*) get_actual_argument(1, FALSE, FALSE);
	height = (int) force_number(tmp);

	glutReshapeWindow(width, height);
	return make_number((AWKNUM) 0);
}

	static NODE *
do_PositionWindow(int nargs)
{
	NODE *tmp;
	int x, y;

	tmp    = (NODE*) get_actual_argument(0, FALSE, FALSE);
	x      = (int) force_number(tmp);

	tmp    = (NODE*) get_actual_argument(1, FALSE, FALSE);
	y      = (int) force_number(tmp);

	glutPositionWindow(x, y);
	return make_number((AWKNUM) 0);
}

static NODE *
do_ShowWindow(int nargs)
{
	glutShowWindow();
	return make_number((AWKNUM) 0);
}

static NODE *
do_HideWindow(int nargs)
{
	glutHideWindow();
	return make_number((AWKNUM) 0);
}

static NODE *
do_IconifyWindow(int nargs)
{
	glutIconifyWindow();
	return make_number((AWKNUM) 0);
}

static NODE *
do_PushWindow(int nargs)
{
	glutPushWindow();
	return make_number((AWKNUM) 0);
}

static NODE *
do_PopWindow(int nargs)
{
	glutPopWindow();
	return make_number((AWKNUM) 0);
}

static NODE *
do_FullScreen(int nargs)
{
	glutFullScreen();
	return make_number((AWKNUM) 0);
}

static NODE *
do_GameMode(int nargs)
{
	NODE *tmp;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);

	//glutGameModeString("1024x768:32@60");
	glutGameModeString(tmp->stptr);
	glutEnterGameMode();

	return make_number((AWKNUM) 0);
}

static NODE *
do_CreateWindow(int nargs)
{
	NODE *tmp;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);

	glutCreateWindow(tmp->stptr);

	set_default_user_func();

	return make_number((AWKNUM) 0);
}

static NODE *
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

static NODE *
do_ReshapeFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Reshape_user_func = func_ptr;

	glutReshapeFunc(AgReshape);
	return make_number((AWKNUM) 0);
}

static NODE *
do_KeyboardFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Keyboard_user_func = func_ptr;

	glutKeyboardFunc(AgKeyboard);
	return make_number((AWKNUM) 0);
}

static NODE *
do_KeyboardUpFunc(int nargs)
{
	NODE *func_ptr = user_func();
	KeyboardUp_user_func = func_ptr;

	glutKeyboardUpFunc(AgKeyboardUp);
	return make_number((AWKNUM) 0);
}

static NODE *
do_SpecialFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Special_user_func = func_ptr;

	glutSpecialFunc(AgSpecial);
	return make_number((AWKNUM) 0);
}

static NODE *
do_SpecialUpFunc(int nargs)
{
	NODE *func_ptr = user_func();
	SpecialUp_user_func = func_ptr;

	glutSpecialUpFunc(AgSpecialUp);
	return make_number((AWKNUM) 0);
}

static NODE *
do_MouseFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Mouse_user_func = func_ptr;

	glutMouseFunc(AgMouse);
	return make_number((AWKNUM) 0);
}

static NODE *
do_MotionFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Motion_user_func = func_ptr;

	glutMotionFunc(AgMotion);
	return make_number((AWKNUM) 0);
}

static NODE *
do_PassiveMotionFunc(int nargs)
{
	NODE *func_ptr = user_func();
	PassiveMotion_user_func = func_ptr;

	glutPassiveMotionFunc(AgPassiveMotion);
	return make_number((AWKNUM) 0);
}

static NODE *
do_GetModifiers(int nargs)
{
	int ret = glutGetModifiers();
	char tmp[4];
	char *tmp_ptr = tmp;

	if (ret & GLUT_ACTIVE_SHIFT) {
		*tmp_ptr = 'S';
		tmp_ptr++;
	}
	if (ret & GLUT_ACTIVE_CTRL) {
		*tmp_ptr = 'C';
		tmp_ptr++;
	}
	if (ret & GLUT_ACTIVE_ALT) {
		*tmp_ptr = 'A';
		tmp_ptr++;
	}
	*tmp_ptr = '\0';

	return make_string(tmp, strlen(tmp));
}

static NODE *
do_EntryFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Entry_user_func = func_ptr;

	glutEntryFunc(AgEntry);
	return make_number((AWKNUM) 0);
}

static NODE *
do_DisplayFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Display_user_func = func_ptr;

	glutDisplayFunc(AgDisplay);
	return make_number((AWKNUM) 0);
}

//void glutTimerFunc(unsigned int msecs, void (*func)(int value), value);
static NODE *
do_TimerFunc(int nargs)
{
	NODE *tmp;
	unsigned int msecs;
	int value;

	tmp   = (NODE*) get_actual_argument(0, FALSE, FALSE);
	msecs = (unsigned int) (force_number(tmp));

	tmp   = (NODE*) get_actual_argument(1, FALSE, FALSE);
	force_string(tmp);
	NODE *fnc_ptr = lookup(tmp->stptr);	//TODO
	if (fnc_ptr == NULL || fnc_ptr->type != Node_func)
		fatal(_("Timer callback function `%s' is not defined"), tmp->stptr);
	Timer_user_func = fnc_ptr;

	tmp   = (NODE*) get_actual_argument(2, FALSE, FALSE);
	value = (int) (force_number(tmp));

	glutTimerFunc(msecs, AgTimer, value);
	return make_number((AWKNUM) 0);
}

static NODE *
user_func(void)
{
	NODE *tmp;
	NODE *fnc_ptr;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);
	
	fnc_ptr = user_func_sub(tmp->stptr);

	if (fnc_ptr == NULL)
		fatal(_("keyboard callback function `%s' is not defined"), tmp->stptr);	//TODO

	return fnc_ptr;
}

static NODE *
user_func_sub(const char * fnc_name)
{
	NODE *fnc_ptr;

	/* fnc_name が存在しないとき、返り値はNULL */
	fnc_ptr = lookup(fnc_name);

	if (fnc_ptr != NULL && fnc_ptr->type != Node_func)
		fnc_ptr = NULL;

	return fnc_ptr;
}

void Idle()
{
	glutPostRedisplay();
}

static NODE *
do_MainLoop(int nargs)
{
	//glutKeyboardFunc(AgKeyboard);
	//glutDisplayFunc(AgDisplay);
	//glutReshapeFunc(AgReshape);
	glutIdleFunc(Idle);
	//glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 光源
	//
	// ライティングを有効にする。
	// ポリゴンの向きや光源からの距離に応じてポリゴンの明るさを計算するようになる。
	// これをやらないと、光源や質感の設定をやっても全く反映されない。
	//glEnable(GL_LIGHTING);
	// ０番の光源を使うようにする。
	// OpenGLでは、GL_LIGHT0?GL_LIGHT7の８つの光源は最低使え、
	// 環境によってはそれ以上の数の光源を使うこともできる。
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT7);

	glutMainLoop();
	return make_number((AWKNUM) 0);
}

static NODE *
do_PostRedisplay(int nargs)
{
	glutPostRedisplay();
	return make_number((AWKNUM) 0);
}

static NODE *
do_SwapBuffers(int nargs)
{
	glutSwapBuffers();
	return make_number((AWKNUM) 0);
}

static NODE *
do_Enable(int nargs)
{
	NODE *tmp;
	GLenum para;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);
	//Todo
	para = enable_disable(tmp->stptr);

	glEnable(para);
	return make_number((AWKNUM) 0);
}

GLenum enable_disable(const char *str)
{
	GLenum para;

	para = light_light_s(str);

	if (!strcmp(str, "LIGHTING")) {
		para = GL_LIGHTING;
	} else if (!strcmp(str, "POINT_SMOOTH")) {
		para = GL_POINT_SMOOTH;
	} else if (!strcmp(str, "LINE_SMOOTH")) {
		para = GL_LINE_SMOOTH;
	}

	return para;
}

static NODE *
do_Disable(int nargs)
{
	NODE *tmp;
	GLenum para;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);
	//Todo
	para = enable_disable(tmp->stptr);

	glDisable(para);
	return make_number((AWKNUM) 0);
}

static NODE *
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

static void
AgKeyboard(unsigned char key, int x, int y)
{
	NODE *args[4];

	if (key > 127) //charで対応できない
		fatal(_("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));

	args[0] = make_string((char *) &key, 1);
	args[1] = make_number((AWKNUM) x);
	args[2] = make_number((AWKNUM) y);
	args[3] = NULL;

	//NODE *arg_key, *arg_x, *arg_y;
	//arg_key = make_string((char)key, 1);
	//arg_x = make_number((AWKNUM) x);
	//arg_y = make_number((AWKNUM) y);

	callback_user_func(Keyboard_user_func, args, 3);

//	freenode(arg_key);
//	freenode(arg_x);
//	freenode(arg_y);

	glutPostRedisplay();
	return;
}

static void
AgKeyboardUp(unsigned char key, int x, int y)
{
	NODE *args[4];

	if (key > 127) //charで対応できない
		fatal(_("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));

	args[0] = make_string((char *) &key, 1);
	args[1] = make_number((AWKNUM) x);
	args[2] = make_number((AWKNUM) y);
	args[3] = NULL;

	callback_user_func(KeyboardUp_user_func, args,3);

	glutPostRedisplay();
	return;
}

static void
AgSpecial(int key, int x, int y)
{
	NODE *args[4];
	const char *key_str = specialkey2str(key);

	args[0] = make_string(key_str, strlen(key_str));
	args[1] = make_number((AWKNUM) x);
	args[2] = make_number((AWKNUM) y);
	args[3] = NULL;

	//NODE *arg_key, *arg_x, *arg_y;
	//arg_key = make_string((char)key, 1);
	//arg_x = make_number((AWKNUM) x);
	//arg_y = make_number((AWKNUM) y);

	callback_user_func(Special_user_func, args, 3);

//	freenode(arg_key);
//	freenode(arg_x);
//	freenode(arg_y);

	glutPostRedisplay();
	return;
}

static void
AgSpecialUp(int key, int x, int y)
{
	NODE *args[4];
	const char *key_str = specialkey2str(key);

	args[0] = make_string(key_str, strlen(key_str));
	args[1] = make_number((AWKNUM) x);
	args[2] = make_number((AWKNUM) y);
	args[3] = NULL;

	callback_user_func(SpecialUp_user_func, args, 3);

	glutPostRedisplay();
	return;
}

static const char *
specialkey2str(int key)
{
	switch (key) {
	case GLUT_KEY_F1:		// F1
		return "F1";
	case GLUT_KEY_F2:		// F2
		return "F2";
	case GLUT_KEY_F3:		// F3
		return "F3";
	case GLUT_KEY_F4:		// F4
		return "F4";
	case GLUT_KEY_F5:		// F5
		return "F5";
	case GLUT_KEY_F6:		// F6
		return "F6";
	case GLUT_KEY_F7:		// F7
		return "F7";
	case GLUT_KEY_F8:		// F8
		return "F8";
	case GLUT_KEY_F9:		// F9
		return "F9";
	case GLUT_KEY_F10:		// F10
		return "F10";
	case GLUT_KEY_F11:		// F11
		return "F11";
	case GLUT_KEY_F12:		// F12
		return "F12";
	case GLUT_KEY_LEFT:		// Left Arrow
		return "LEFT";
	case GLUT_KEY_UP:		// Up Arrow
		return "UP";
	case GLUT_KEY_RIGHT:		// Right Arrow
		return "RIGHT";
	case GLUT_KEY_DOWN:		// Down Arrow
		return "DOWN";
	case GLUT_KEY_PAGE_UP:		// Page up
		return "PAGE_UP";
	case GLUT_KEY_PAGE_DOWN:	// Page down
		return "PAGE_DOWN";
	case GLUT_KEY_HOME:		// Home
		return "HOME";
	case GLUT_KEY_END:		// End
		return "END";
	case GLUT_KEY_INSERT:		// Inset
		return "INSERT";
	default:			// ToDo warning
		return "";
	}
	// エスケープ，バックスペース，デリートキーは
	// ASCII キャラクターとして生成されるという点に注意．
}

static void
AgMouse(int button, int state, int x, int y)
{
    // TODO  argsをstaticにして、高速化する
    // いや、それをすると、引数がユーザランドで書き換えられたときに、困る。
    // なら、汚いが、領域確保のも、初期化時にしておいて、呼び出し時には値の設定のみする？

	NODE *args[5];
	char *btn_str;
	char *stt_str;

	switch (button) {
	case GLUT_LEFT_BUTTON:
	    btn_str = "left";
	    break;
	case GLUT_MIDDLE_BUTTON:
	    btn_str = "middle";
	    break;
	case GLUT_RIGHT_BUTTON:
	    btn_str = "right";
	    break;
	default:
	    btn_str = "unknown";
	    break;
	}

	switch (state) {
	case GLUT_UP:
	    stt_str = "up";
	    break;
	case GLUT_DOWN:
	    stt_str = "down";
	    break;
	}

	//on gawk, not needed terminate with null character
	args[0] = make_string(btn_str, strlen(btn_str));
	args[1] = make_string(stt_str, strlen(stt_str));
	args[2] = make_number((AWKNUM) x);
	args[3] = make_number((AWKNUM) y);
	args[4] = NULL;

	callback_user_func(Mouse_user_func, args, 4);

	glutPostRedisplay();
	return;
}

static void
AgMotion(int x, int y)
{
	NODE *args[3];

	args[0] = make_number((AWKNUM) x);
	args[1] = make_number((AWKNUM) y);
	args[2] = NULL;

	callback_user_func(Motion_user_func, args, 2);

	glutPostRedisplay();
	return;
}

static void
AgPassiveMotion(int x, int y)
{
	NODE *args[3];

	args[0] = make_number((AWKNUM) x);
	args[1] = make_number((AWKNUM) y);
	args[2] = NULL;

	callback_user_func(PassiveMotion_user_func, args, 2);

	//glutPostRedisplay();
	return;
}

static void
AgEntry(int state)
{
	NODE *args[2];

	args[0] = make_number((AWKNUM) state);
	args[1] = NULL;

	callback_user_func(Entry_user_func, args, 2);
	return;
}

static void
AgDisplay(void)
{
	//glClearColor(21/255,10/255,89/255,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT);

	NODE *args[1];
	args[0] = NULL;
	glEnable(GL_DEPTH_TEST);
	callback_user_func(Display_user_func, args, 0);
	glDisable(GL_DEPTH_TEST);
/*
	glBegin(GL_POLYGON);
	glColor3d(1.0, 0.0, 0.0); // 赤
	glVertex2d(-0.5, -0.5);
	glColor3d(0.0, 1.0, 0.0); // 緑
	glVertex2d(0.5, -0.5);
	glColor3d(0.0, 0.0, 1.0); // 青
	glVertex2d(0.5, 0.5);
	glColor3d(1.0, 1.0, 0.0); // 黄
	glVertex2d(-0.5, 0.5);
	glEnd();
*/
	//glFlush();
	glutSwapBuffers();
}

static void AgTimer(int value)
{
	NODE *args[2];

	args[0] = make_number((AWKNUM) value);
	args[1] = NULL;

	callback_user_func(Timer_user_func, args, 1);
	glutPostRedisplay();
	return;
}

AWKNUM
callback_user_func(NODE *func_ptr, NODE *args[], int argc)
{
	AWKNUM ret;
	int i;
	INSTRUCTION *code = NULL;
	extern int exiting;

	/* make function call instructions */
	code = bcalloc(Op_func_call, 2, 0);
	code->func_body = func_ptr;
	code->func_name = NULL;		/* not needed, func_body already assigned */
	(code + 1)->expr_count = argc;	/* function takes 3 arguments */
	code->nexti = bcalloc(Op_stop, 1, 0);	

	/* make non-local jumps `next' and `nextfile' fatal in
	 * callback function by setting currule in interpret()
	 * to undefined (0). `exit' is handled in sort_user_func.
	 */

	extern int currule;
	(code + 1)->inrule = currule;	/* save current rule */
	currule = 0;

	for (i = 0; args[i] != NULL; i++) { PUSH(args[i]); }

	interpret(code);
	if (exiting)	/* do not assume anything about the user-defined function! */
		gawk_exit(exit_val);

	POP_NUMBER(ret);

	currule = (code + 1)->inrule;   /* restore current rule */ 
	bcfree(code->nexti);            /* Op_stop */
	bcfree(code);                   /* Op_func_call */

	return (ret < 0.0) ? -1 : (ret > 0.0);
}

static void AgReshape(int w, int h)
{
	NODE *args[3];

	args[0] = make_number((AWKNUM) w);
	args[1] = make_number((AWKNUM) h);
	args[2] = NULL;

	callback_user_func(Reshape_user_func, args, 2);
	return;
}

static NODE *
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
	}

	glBegin(type);
	return make_number((AWKNUM) 0);
}

static NODE *
do_End(int nargs)
{
	glEnd();
	return make_number((AWKNUM) 0);
}

static NODE *
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

static NODE *
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

static NODE *
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

static NODE *
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


static NODE *
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

static NODE *
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

static NODE *
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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, aspect, front, back);
	return make_number((AWKNUM) 0);
}

static NODE *
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
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	return make_number((AWKNUM) 0);
}

// 回転、移動、サイズ変更

static NODE *
do_LoadIdentity(int nargs)
{
	if (do_lint && get_curfunc_arg_count() > 0)
		lintwarn("LoadIdentity: called with too many arguments");

	glLoadIdentity();
	return make_number((AWKNUM) 0);
}

static NODE *
do_PushMatrix(int nargs)
{
	if (do_lint && get_curfunc_arg_count() > 0)
		lintwarn("PushMatrix: called with too many arguments");

	glPushMatrix();
	return make_number((AWKNUM) 0);
}

static NODE *
do_PopMatrix(int nargs)
{
	if (do_lint && get_curfunc_arg_count() > 0)
		lintwarn("PopMatrix: called with too many arguments");

	glPopMatrix();
	return make_number((AWKNUM) 0);
}

static NODE *
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

static NODE *
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

static NODE *
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

static NODE *
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
	type = draw_pixels_format(tmp->stptr);

	tmp    = (NODE*) get_actual_argument(3, FALSE, FALSE);
	force_string(tmp);
	type = draw_pixels_type(tmp->stptr);

	tmp    = (NODE*) get_actual_argument(4, FALSE, FALSE);
	force_string(tmp);
	//type = get_draw_pixels(tmp->stptr);

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

// 光源
static NODE *
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

GLenum light_light_s(const char *str)
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

GLenum light_light_n(int num)
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
GLenum light_pname(const char *str)
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
	}

	return pname;
}

// 法線ベクトル
static NODE *
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
static NODE *
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

GLenum material_face(const char *str)
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
GLenum material_pname(const char *str)
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
	}

	return pname;
}

static NODE *
do_PointSize(int nargs)
{
	NODE *tmp;
	GLfloat size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLfloat) force_number(tmp);

	glPointSize(size);
	return make_number((AWKNUM) 0);
}

static NODE *
do_LineWidth(int nargs)
{
	NODE *tmp;
	GLfloat width;

	tmp   = (NODE*) get_actual_argument(0, FALSE, FALSE);
	width = (GLfloat) force_number(tmp);

	glLineWidth(width);
	return make_number((AWKNUM) 0);
}

static NODE *
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
	}
}

static NODE *
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

static NODE *
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

static NODE *
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

static NODE *
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

static NODE *
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

static NODE *
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

	glutSolidCylinder(base, height, slices, stacks);
	return make_number((AWKNUM) 0);
}

static NODE *
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

	glutWireCylinder(base, height, slices, stacks);
	return make_number((AWKNUM) 0);
}

// トーラス(ドーナツ)

static NODE *
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

static NODE *
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

static NODE *
do_SolidCube(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glutSolidCube(size);
	return make_number((AWKNUM) 0);
}

static NODE *
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

static NODE *
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

static NODE *
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

static NODE *
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

static NODE *
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

static NODE *
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

static NODE *
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

static NODE *
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

static NODE *
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

static NODE *
do_SolidTeapot(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glutSolidTeapot(size);
	return make_number((AWKNUM) 0);
}

static NODE *
do_WireTeapot(int nargs)
{
	NODE *tmp;
	GLdouble size;

	tmp  = (NODE*) get_actual_argument(0, FALSE, FALSE);
	size = (GLdouble) force_number(tmp);

	glutWireTeapot(size);
	return make_number((AWKNUM) 0);
}

static NODE *
do_pi(int nargs)
{
	if (do_lint && get_curfunc_arg_count() > 0)
		lintwarn("pi: called with too many arguments");

	return make_number((AWKNUM) M_PI);
}

static NODE *
do_d2r(int nargs)
{
	NODE *tmp;

	if (do_lint && get_curfunc_arg_count() > 1)
		lintwarn("d2r: called with too many arguments");

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	if (tmp != NULL) {
		return make_number((AWKNUM) (force_number(tmp) * M_PI / 180));
	} else {
		fatal(_("d2r: called with no arguments"));
	}
}

static NODE *
do_r2d(int nargs)
{
	NODE *tmp;

	if (do_lint && get_curfunc_arg_count() > 1)
		lintwarn("r2d: called with too many arguments");

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	if (tmp != NULL) {
		return make_number((AWKNUM) (force_number(tmp) * 180 / M_PI));
	} else {
		fatal(_("r2d: called with no arguments"));
	}
}

// 円
static NODE *
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
	for (i = 0; i <= slices; i++) {
		glVertex2d(radius * cos(i * a), radius * sin(i * a));
	}
	glEnd();

	return make_number((AWKNUM) 0);
}

static NODE *
do_DrawAxes(int nargs)
{
	NODE *tmp;
	GLdouble len;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	len = (GLdouble) force_number(tmp);
//TODO Lighting
	//glPushMatrix();
	//glLoadIdentity();
	//glLineWidth(2.0);
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
	//glPopMatrix();

	return make_number((AWKNUM) 0);
}


