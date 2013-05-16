/*
 * awkgl.h
 */

#ifndef _AWK_GL_H
#define _AWK_GL_H

#ifdef HAVE_FREEGLUT
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "awk.h"

/* device.c */
extern NODE *Keyboard_user_func;
extern NODE *KeyboardUp_user_func;
extern NODE *Special_user_func;
extern NODE *SpecialUp_user_func;
extern NODE *Mouse_user_func;
extern NODE *Motion_user_func;
extern NODE *PassiveMotion_user_func;
#ifdef HAVE_FREEGLUT
extern NODE *MouseWheel_user_func;
#endif
extern NODE *Entry_user_func;

/* loop.c */
extern NODE *Display_user_func;
extern NODE *Idle_user_func;
extern NODE *Timer_user_func;

/* window.c */
extern NODE *Reshape_user_func;
#ifdef HAVE_FREEGLUT
extern NODE *Close_user_func;
extern NODE *WMClose_user_func;
#endif

/* bitmap.c */
extern NODE *do_DrawPixels(int);

/* device.c */
extern NODE *do_KeyboardFunc(int);
extern NODE *do_KeyboardUpFunc(int);
extern NODE *do_SpecialFunc(int);
extern NODE *do_SpecialUpFunc(int);
extern NODE *do_MouseFunc(int);
extern NODE *do_MotionFunc(int);
extern NODE *do_PassiveMotionFunc(int);
extern NODE *do_GetModifiers(int);
#ifdef HAVE_FREEGLUT
extern NODE *do_MouseWheelFunc(int);
#endif
extern NODE *do_EntryFunc(int);
extern void AgKeyboard(unsigned char, int, int);
extern void AgKeyboardUp(unsigned char, int, int);
extern void AgSpecial(int, int, int);
extern void AgSpecialUp(int, int, int);
extern void AgMouse(int, int, int, int);
extern void AgMotion(int, int);
extern void AgPassiveMotion(int, int);
#ifdef HAVE_FREEGLUT
extern void AgMouseWheel(int, int, int, int);
#endif
extern void AgEntry(int);

/* device.c */
extern NODE *do_MainLoop(int);
extern NODE *do_MainLoopEvent(int);
extern NODE *do_LeaveMainLoop(int);
extern NODE *do_Exit(int);
extern NODE *do_DisplayFunc(int);
extern NODE *do_IdleFunc(int);
extern NODE *do_TimerFunc(int);
extern NODE *do_PostRedisplay(int);
extern NODE *do_PostWindowRedisplay(int);
extern void AgDisplay(void);
extern void AgIdle(void);
extern void AgTimer(int);

/* draw_geometry.c */
extern NODE *do_SolidSphere(int);
extern NODE *do_WireSphere(int);
extern NODE *do_SolidCone(int);
extern NODE *do_WireCone(int);
extern NODE *do_SolidCylinder(int);
extern NODE *do_WireCylinder(int);
extern NODE *do_SolidTorus(int);
extern NODE *do_WireTorus(int);
extern NODE *do_SolidCube(int);
extern NODE *do_WireCube(int);
extern NODE *do_SolidTetrahedron(int);
extern NODE *do_WireTetrahedron(int);
extern NODE *do_SolidOctahedron(int);
extern NODE *do_WireOctahedron(int);
extern NODE *do_SolidDodecahedron(int);
extern NODE *do_WireDodecahedron(int);
extern NODE *do_SolidIcosahedron(int);
extern NODE *do_WireIcosahedron(int);
extern NODE *do_SolidTeapot(int);
extern NODE *do_WireTeapot(int);
//extern NODE *do_Point(int);
//extern NODE *do_Line(int);
extern NODE *do_DrawCircle(int nargs);
extern NODE *do_DrawAxes(int);
//extern NODE *do_DrawSolidFace(int);
//extern NODE *do_DrawWireFace(int);

/* material.c */
extern NODE *do_ClearColor(int);
extern NODE *do_Color(int);
extern NODE *do_Light(int);
extern NODE *do_Normal(int);
extern NODE *do_Material(int);

/* matrix.c */
extern NODE *do_MatrixMode(int);
extern NODE *do_LoadIdentity(int);
extern NODE *do_PushMatrix(int);
extern NODE *do_PopMatrix(int);
extern NODE *do_MultMatrix(int);
extern NODE *do_Rotate(int);
extern NODE *do_Transrate(int);
extern NODE *do_Scale(int);

/* util.c */
extern NODE *do_pi(int);
extern NODE *do_d2r(int);
extern NODE *do_r2d(int);

/* window.c */
extern NODE *do_CreateWindow(int);
extern NODE *do_CreateSubWindow(int);
extern NODE *do_DestroyWindow(int);
#ifdef HAVE_FREEGLUT
extern NODE *do_CloseFunc(int);
extern NODE *do_WMCloseFunc(int);
#endif
extern NODE *do_GetWindow(int);
extern NODE *do_SetWindow(int);
extern NODE *do_SetWindowPosSize(int);	/* Only awkGL */
extern NODE *do_PositionWindow(int);
extern NODE *do_ReshapeWindow(int);
extern NODE *do_SetWindowTitle(int);
extern NODE *do_SetIconTitle(int);
extern NODE *do_ShowWindow(int);
extern NODE *do_HideWindow(int);
extern NODE *do_IconifyWindow(int);
extern NODE *do_PushWindow(int);
extern NODE *do_PopWindow(int);
extern NODE *do_FullScreen(int);
#if 0
extern NODE *do_LeaveFullScreen(int);
#endif
extern NODE *do_FullScreenToggle(int);
/* extern NODE *do_GameMode(int); */
extern NODE *do_ReshapeFunc(int);
extern void AgReshape(int, int);
#ifdef HAVE_FREEGLUT
extern void AgClose(void);
extern void AgWMClose(void);
#endif

/* veiw.c */
extern NODE *do_Viewport(int);
extern NODE *do_Ortho(int);
extern NODE *do_Frustum(int);
extern NODE *do_Perspective(int);
extern NODE *do_Lookat(int);

/* vertex.c */
extern NODE *do_Begin(int);
extern NODE *do_End(int);
extern NODE *do_Vertex2d(int);
extern NODE *do_Vertex3d(int);

/* misc.c */
extern NODE *do_SwapBuffers(int);
extern NODE *do_Enable(int);
extern NODE *do_Disable(int);
extern NODE *do_IsEnabled(int);
extern NODE *do_PointSize(int);
extern NODE *do_LineWidth(int);
extern NODE *do_LineStipple(int);
extern NODE *do_PolygonMode(int);
extern NODE *do_FrontFace(int);
extern NODE *do_CullFace(int);
extern NODE *do_PolygonOffset(int);

/* material.c */
extern GLenum light_light_s(const char *);
extern GLenum material_face(const char *);

void set_default_user_func(void);
NODE *user_func(void);
AWKNUM callback_user_func(NODE *, NODE *[], int);

#define skip_str(ptr, string)	\
	if (!strncmp(ptr, string, sizeof(string))) {\
		ptr += sizeof(string);\
	}

#endif /* _AWK_GL_H */
