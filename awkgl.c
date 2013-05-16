/*
 * awkgl.c
 */

#include "awkgl.h"

int plugin_is_GPL_compatible;

static void Idle(void);
static NODE *user_func_sub(const char *);

NODE *
dlload(NODE *tree, void *dl)
{
/* bitmap.c */
	make_builtin("RasterPos", do_RasterPos, 3);
	make_builtin("PixelZoom", do_PixelZoom, 2);
	make_builtin("DrawPixels", do_DrawPixels, 5);

/* device.c */
	make_builtin("KeyboardFunc", do_KeyboardFunc, 1);
	make_builtin("KeyboardUpFunc", do_KeyboardUpFunc, 1);
	make_builtin("SpecialFunc", do_SpecialFunc, 1);
	make_builtin("SpecialUpFunc", do_SpecialUpFunc, 1);
	make_builtin("MouseFunc", do_MouseFunc, 1);
	make_builtin("MotionFunc", do_MotionFunc, 1);
	make_builtin("PassiveMotionFunc", do_PassiveMotionFunc, 1);
	make_builtin("GetModifiers", do_GetModifiers, 0);
#ifdef HAVE_FREEGLUT
	make_builtin("MouseWheel", do_MouseWheelFunc, 1);
#endif
	make_builtin("EntryFunc", do_EntryFunc, 1);

/* draw_geometry.c */
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
	// make_builtin("Point", do_Point, 3);
	// make_builtin("Line", do_Line, 3);
	make_builtin("DrawCircle", do_DrawCircle, 3);
	make_builtin("DrawAxes", do_DrawAxes, 1);

/* font.c */
	make_builtin("BitmapCharacter", do_BitmapCharacter, 2);
	make_builtin("BitmapWidth", do_BitmapWidth, 2);
	make_builtin("BitmapLength", do_BitmapLength, 2);
#if FREEGLUT
	make_builtin("BitmapHeight", do_BitmapHeight, 1);
	make_builtin("BitmapString", do_BitmapString, 2);
#endif
	make_builtin("StrokeCharacter", do_StrokeCharacter, 2);
	make_builtin("StrokeWidth", do_StrokeWidth, 2);
	make_builtin("StrokeLength", do_StrokeLength, 2);
#if FREEGLUT
	make_builtin("StrokeHeight", do_StrokeHeight, 1);
	make_builtin("StrokeString", do_StrokeString, 2);
#endif

/* loop.c */
	make_builtin("MainLoop", do_MainLoop, 0);
	make_builtin("MainLoopEvent", do_MainLoopEvent, 0);
	make_builtin("LeaveMainLoop", do_LeaveMainLoop, 0);
	make_builtin("Exit", do_Exit, 0);
	make_builtin("DisplayFunc", do_DisplayFunc, 1);
	make_builtin("IdleFunc", do_IdleFunc, 1);
	make_builtin("TimerFunc", do_TimerFunc, 3);
	make_builtin("PostRedisplay", do_PostRedisplay, 0);
	make_builtin("PostWindowRedisplay", do_PostWindowRedisplay, 1);

/* material.c */
	make_builtin("ClearColor", do_ClearColor, 3);
	make_builtin("Color", do_Color, 3);
	make_builtin("Light", do_Light, 9);
	make_builtin("Normal", do_Normal, 3);
	make_builtin("Material", do_Material, 8);

/* matrix.c */
	make_builtin("MatrixMode", do_MatrixMode, 1);
	make_builtin("LoadIdentity", do_LoadIdentity, 1);
	make_builtin("PushMatrix", do_PushMatrix, 1);
	make_builtin("PopMatrix", do_PopMatrix, 1);
	make_builtin("MultMatrix", do_MultMatrix, 16);//TODO
	make_builtin("Rotate", do_Rotate, 4);
	make_builtin("Translate", do_Transrate, 4);
	make_builtin("Scale", do_Scale, 4);

/* misc.c */
	make_builtin("SwapBuffers", do_SwapBuffers, 0);
	make_builtin("Enable", do_Enable, 1);
	make_builtin("Disable", do_Disable, 1);
	make_builtin("IsEnabled", do_IsEnabled, 1);
	make_builtin("PointSize", do_PointSize, 1);
	make_builtin("LineWidth", do_LineWidth, 1);
	make_builtin("LineStipple", do_LineStipple, 2);
	make_builtin("PolygonMode", do_PolygonMode, 2);
	make_builtin("FrontFace", do_FrontFace, 1);
	make_builtin("CullFace", do_CullFace, 1);
	make_builtin("PolygonOffset", do_PolygonOffset, 2);

/* util.c */
	make_builtin("pi", do_pi, 1);
	make_builtin("radian", do_d2r, 1);
	make_builtin("degree", do_r2d, 1);
	make_builtin("d2r", do_d2r, 1);
	make_builtin("r2d", do_r2d, 1);
	make_builtin("deg2rad", do_d2r, 1);
	make_builtin("rad2deg", do_r2d, 1);

/* veiw.c */
	make_builtin("Viewport", do_Viewport, 4);
	make_builtin("Ortho", do_Ortho, 6);
	make_builtin("Frustum", do_Frustum, 6);
	make_builtin("Perspective", do_Perspective, 4);
	make_builtin("LookAt", do_Lookat, 9);

/* vertex.c */
	make_builtin("Begin", do_Begin, 3);
	make_builtin("End", do_End, 3);
	make_builtin("Vertex2d", do_Vertex2d, 2);
	make_builtin("Vertex3d", do_Vertex3d, 3);

/* window.c */
	make_builtin("CreateWindow", do_CreateWindow, 1);
	make_builtin("CreateSubWindow", do_CreateSubWindow, 5);
	make_builtin("DestoyWindow", do_DestroyWindow, 1);
#ifdef HAVE_FREEGLUT
	make_builtin("Close", do_CloseFunc, 1);
	make_builtin("WMClose", do_WMCloseFunc, 1);
#endif
	make_builtin("GetWindow", do_GetWindow, 0);
	make_builtin("SetWindow", do_SetWindow, 1);
	make_builtin("SetWindowPosSize", do_SetWindowPosSize, 4);
	make_builtin("PositionWindow", do_PositionWindow, 2);
	make_builtin("ReshapeWindow", do_ReshapeWindow, 2);
	make_builtin("SetWindowTitle", do_SetWindowTitle, 1);
	make_builtin("SetIconTitle", do_SetIconTitle, 1);
	make_builtin("ShowWindow", do_ShowWindow, 0);
	make_builtin("HideWindow", do_HideWindow, 0);
	make_builtin("IconifyWindow", do_IconifyWindow, 0);
	make_builtin("PushWindow", do_PushWindow, 0);
	make_builtin("PopWindow", do_PopWindow, 0);
	make_builtin("FullScreen", do_FullScreen, 0);
#if 0
	make_builtin("LeaveFullScreen", do_LeaveFullScreen, 0);
#endif
	make_builtin("FullScreenToggle", do_FullScreenToggle, 0);
	// make_builtin("GameMode", do_GameMode, 1);
	make_builtin("ReshapeFunc", do_ReshapeFunc, 4);

	int argc=0; char *argv[1]; glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	return make_number((AWKNUM) 0);
}

static void
Idle()
{
	glutPostRedisplay();
}

void
set_default_user_func()
{
	NODE *fnc_ptr;

	fnc_ptr = user_func_sub("idle");
	if (fnc_ptr != NULL) {
		Idle_user_func = fnc_ptr;
		glutIdleFunc(AgIdle);
	} else {
		glutIdleFunc(Idle);
	}

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

#ifdef HAVE_FREEGLUT
	fnc_ptr = user_func_sub("MouseWheel");
	if (fnc_ptr != NULL) {
		MouseWheel_user_func = fnc_ptr;
		glutMouseWheelFunc(AgMouseWheel);
	}

	fnc_ptr = user_func_sub("Close");
	if (fnc_ptr != NULL) {
		Close_user_func = fnc_ptr;
		glutCloseFunc(AgClose);
	}

	fnc_ptr = user_func_sub("WMClose");
	if (fnc_ptr != NULL) {
		WMClose_user_func = fnc_ptr;
		glutWMCloseFunc(AgWMClose);
	}
#endif

	return;
}

NODE *
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

	// extern int currule;
	// (code + 1)->inrule = currule;	/* save current rule */
	//currule = 0;	//TODO

	for (i = 0; args[i] != NULL; i++) { PUSH(args[i]); }

	interpret(code);
	if (exiting)	/* do not assume anything about the user-defined function! */
		gawk_exit(exit_val);

	POP_NUMBER(ret);

	// currule = (code + 1)->inrule;   /* restore current rule */ 
	bcfree(code->nexti);            /* Op_stop */
	bcfree(code);                   /* Op_func_call */

	return (ret < 0.0) ? -1 : (ret > 0.0);
}
