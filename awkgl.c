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
	make_builtin("glRasterPos", do_RasterPos, 4);
	make_builtin("glPixelZoom", do_PixelZoom, 2);
	make_builtin("glDrawPixels", do_DrawPixels, 5);
	make_builtin("glWindowPos", do_WindowPos, 3);

/* device.c */
	make_builtin("glutKeyboardFunc", do_KeyboardFunc, 1);
	make_builtin("glutKeyboardUpFunc", do_KeyboardUpFunc, 1);
	make_builtin("glutSpecialFunc", do_SpecialFunc, 1);
	make_builtin("glutSpecialUpFunc", do_SpecialUpFunc, 1);
	make_builtin("glutMouseFunc", do_MouseFunc, 1);
	make_builtin("glutMotionFunc", do_MotionFunc, 1);
	make_builtin("glutPassiveMotionFunc", do_PassiveMotionFunc, 1);
	make_builtin("glutGetModifiers", do_GetModifiers, 0);
#ifdef HAVE_FREEGLUT
	make_builtin("glutMouseWheel", do_MouseWheelFunc, 1);
#endif
	make_builtin("glutEntryFunc", do_EntryFunc, 1);

/* draw_geometry.c */
	make_builtin("glutSolidSphere", do_SolidSphere, 3);
	make_builtin("glutWireSphere", do_WireSphere, 3);
	make_builtin("glutSolidCone", do_SolidCone, 4);
	make_builtin("glutWireCone", do_WireCone, 4);
	make_builtin("glutSolidCylinder", do_SolidCylinder, 4);
	make_builtin("glutWireCylinder", do_WireCylinder, 4);
	make_builtin("glutSolidTorus", do_SolidTorus, 4);
	make_builtin("glutWireTorus", do_WireTorus, 4);
	make_builtin("glutSolidCube", do_SolidCube, 1);
	make_builtin("glutWireCube", do_WireCube, 1);
	make_builtin("glutSolidTetrahedron", do_SolidTetrahedron, 1);
	make_builtin("glutWireTetrahedron", do_WireTetrahedron, 1);
	make_builtin("glutSolidOctahedron", do_SolidOctahedron, 1);
	make_builtin("glutWireOctahedron", do_WireOctahedron, 1);
	make_builtin("glutSolidDodecahedron", do_SolidDodecahedron, 1);
	make_builtin("glutWireDodecahedron", do_WireDodecahedron, 1);
	make_builtin("glutSolidIcosahedron", do_SolidIcosahedron, 1);
	make_builtin("glutWireIcosahedron", do_WireIcosahedron, 1);
	make_builtin("glutSolidTeapot", do_SolidTeapot, 1);
	make_builtin("glutWireTeapot", do_WireTeapot, 1);
	// make_builtin("glutPoint", do_Point, 3);
	// make_builtin("glutLine", do_Line, 3);
	make_builtin("glutDrawCircle", do_DrawCircle, 3);
	make_builtin("glutDrawAxes", do_DrawAxes, 1);

/* font.c */
	make_builtin("glutBitmapCharacter", do_BitmapCharacter, 2);
	make_builtin("glutBitmapWidth", do_BitmapWidth, 2);
	make_builtin("glutBitmapLength", do_BitmapLength, 2);
#if FREEGLUT
	make_builtin("glutBitmapHeight", do_BitmapHeight, 1);
	make_builtin("glutBitmapString", do_BitmapString, 2);
#endif
	make_builtin("glutStrokeCharacter", do_StrokeCharacter, 2);
	make_builtin("glutStrokeWidth", do_StrokeWidth, 2);
	make_builtin("glutStrokeLength", do_StrokeLength, 2);
#if FREEGLUT
	make_builtin("glutStrokeHeight", do_StrokeHeight, 1);
	make_builtin("glutStrokeString", do_StrokeString, 2);
#endif

/* loop.c */
	make_builtin("glutMainLoop", do_MainLoop, 0);
	make_builtin("glutMainLoopEvent", do_MainLoopEvent, 0);
	make_builtin("glutLeaveMainLoop", do_LeaveMainLoop, 0);
	make_builtin("glutExit", do_Exit, 0);
	make_builtin("glutDisplayFunc", do_DisplayFunc, 1);
	make_builtin("glutIdleFunc", do_IdleFunc, 1);
	make_builtin("glutTimerFunc", do_TimerFunc, 3);
	make_builtin("glutPostRedisplay", do_PostRedisplay, 0);
	make_builtin("glutPostWindowRedisplay", do_PostWindowRedisplay, 1);

/* material.c */
	make_builtin("glClearColor", do_ClearColor, 3);
	make_builtin("glColor", do_Color, 3);
	make_builtin("glLight", do_Light, 9);
	make_builtin("glNormal", do_Normal, 3);
	make_builtin("glMaterial", do_Material, 8);

/* matrix.c */
	make_builtin("glMatrixMode", do_MatrixMode, 1);
	make_builtin("glLoadIdentity", do_LoadIdentity, 1);
	make_builtin("glPushMatrix", do_PushMatrix, 1);
	make_builtin("glPopMatrix", do_PopMatrix, 1);
	make_builtin("glMultMatrix", do_MultMatrix, 16);//TODO
	make_builtin("glRotate", do_Rotate, 4);
	make_builtin("glTranslate", do_Transrate, 4);
	make_builtin("glScale", do_Scale, 4);

/* misc.c */
	make_builtin("glSwapBuffers", do_SwapBuffers, 0);
	make_builtin("glEnable", do_Enable, 1);
	make_builtin("glDisable", do_Disable, 1);
	make_builtin("glIsEnabled", do_IsEnabled, 1);
	make_builtin("glPointSize", do_PointSize, 1);
	make_builtin("glLineWidth", do_LineWidth, 1);
	make_builtin("glLineStipple", do_LineStipple, 2);
	make_builtin("glPolygonMode", do_PolygonMode, 2);
	make_builtin("glFrontFace", do_FrontFace, 1);
	make_builtin("glCullFace", do_CullFace, 1);
	make_builtin("glPolygonOffset", do_PolygonOffset, 2);

/* util.c */
	make_builtin("pi", do_pi, 1);
	make_builtin("radian", do_d2r, 1);
	make_builtin("degree", do_r2d, 1);
	make_builtin("d2r", do_d2r, 1);
	make_builtin("r2d", do_r2d, 1);
	make_builtin("deg2rad", do_d2r, 1);
	make_builtin("rad2deg", do_r2d, 1);

/* veiw.c */
	make_builtin("glViewport", do_Viewport, 4);
	make_builtin("glOrtho", do_Ortho, 6);
	make_builtin("glFrustum", do_Frustum, 6);
	make_builtin("gluPerspective", do_Perspective, 4);
	make_builtin("gluLookAt", do_Lookat, 9);

/* vertex.c */
	make_builtin("glBegin", do_Begin, 3);
	make_builtin("glEnd", do_End, 3);
	make_builtin("glVertex2d", do_Vertex2d, 2);
	make_builtin("glVertex3d", do_Vertex3d, 3);

/* window.c */
	make_builtin("glutCreateWindow", do_CreateWindow, 1);
	make_builtin("glutCreateSubWindow", do_CreateSubWindow, 5);
	make_builtin("glutDestoyWindow", do_DestroyWindow, 1);
#ifdef HAVE_FREEGLUT
	make_builtin("glutClose", do_CloseFunc, 1);
	make_builtin("glutWMClose", do_WMCloseFunc, 1);
#endif
	make_builtin("glutGetWindow", do_GetWindow, 0);
	make_builtin("glutSetWindow", do_SetWindow, 1);
	make_builtin("glutSetWindowPosSize", do_SetWindowPosSize, 4);
	make_builtin("glutPositionWindow", do_PositionWindow, 2);
	make_builtin("glutReshapeWindow", do_ReshapeWindow, 2);
	make_builtin("glutSetWindowTitle", do_SetWindowTitle, 1);
	make_builtin("glutSetIconTitle", do_SetIconTitle, 1);
	make_builtin("glutShowWindow", do_ShowWindow, 0);
	make_builtin("glutHideWindow", do_HideWindow, 0);
	make_builtin("glutIconifyWindow", do_IconifyWindow, 0);
	make_builtin("glutPushWindow", do_PushWindow, 0);
	make_builtin("glutPopWindow", do_PopWindow, 0);
	make_builtin("glutFullScreen", do_FullScreen, 0);
#if 0
	make_builtin("glutLeaveFullScreen", do_LeaveFullScreen, 0);
#endif
	make_builtin("glutFullScreenToggle", do_FullScreenToggle, 0);
	// make_builtin("glutGameMode", do_GameMode, 1);
	make_builtin("glutReshapeFunc", do_ReshapeFunc, 4);

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
