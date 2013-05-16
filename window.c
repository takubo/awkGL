/*
 * window.c
 */

#include "awkgl.h"

NODE *Reshape_user_func = NULL;
#ifdef HAVE_FREEGLUT
NODE *Close_user_func = NULL;
NODE *WMClose_user_func = NULL;
#endif

NODE *do_CreateWindow(int);
NODE *do_CreateSubWindow(int);
NODE *do_DestroyWindow(int);
#ifdef HAVE_FREEGLUT
NODE *do_CloseFunc(int);
NODE *do_WMCloseFunc(int);
#endif

NODE *do_GetWindow(int);
NODE *do_SetWindow(int);

NODE *do_SetWindowPosSize(int);	/* Only awkGL */
NODE *do_PositionWindow(int);
NODE *do_ReshapeWindow(int);

NODE *do_SetWindowTitle(int);
NODE *do_SetIconTitle(int);

NODE *do_ShowWindow(int);
NODE *do_HideWindow(int);
NODE *do_IconifyWindow(int);

NODE *do_PushWindow(int);
NODE *do_PopWindow(int);

NODE *do_FullScreen(int);
#if 0
NODE *do_LeaveFullScreen(int);
#endif
NODE *do_FullScreenToggle(int);
/* static NODE *do_GameMode(int); */

NODE *do_ReshapeFunc(int);

void AgReshape(int, int);
#ifdef HAVE_FREEGLUT
void AgClose(void);
void AgWMClose(void);
#endif

NODE *
do_CreateWindow(int nargs)
{
	NODE *tmp;
	int win;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);

	win = glutCreateWindow(tmp->stptr);

	set_default_user_func();

	return make_number((AWKNUM) win);
}

NODE *
do_CreateSubWindow(int nargs)
{
	NODE *tmp;
	int window, x, y, width, height;

	tmp    = (NODE*) get_scalar_argument(0, FALSE);
	window = (int) force_number(tmp);

	tmp    = (NODE*) get_scalar_argument(1, FALSE);
	x      = (int) force_number(tmp);

	tmp    = (NODE*) get_scalar_argument(2, FALSE);
	y      = (int) force_number(tmp);

	tmp    = (NODE*) get_scalar_argument(3, FALSE);
	width  = (int) force_number(tmp);

	tmp    = (NODE*) get_scalar_argument(4, FALSE);
	height = (int) force_number(tmp);

	return make_number((AWKNUM) glutCreateSubWindow(window, x, y, width, height));
}

NODE *
do_DestroyWindow(int nargs)
{
	NODE *tmp;
	int window;

	tmp    = (NODE *) get_scalar_argument(0, FALSE);
	window = (int) force_number(tmp);

	glutDestroyWindow(window);
	return make_number((AWKNUM) 0);
}

#ifdef HAVE_FREEGLUT
NODE *
do_CloseFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Close_user_func = func_ptr;

	glutCloseFunc(AgClose);
	return make_number((AWKNUM) 0);
}

NODE *
do_WMCloseFunc(int nargs)
{
	NODE *func_ptr = user_func();
	WMClose_user_func = func_ptr;

	glutWMCloseFunc(AgWMClose);
	return make_number((AWKNUM) 0);
}
#endif

NODE *
do_GetWindow(int nargs)
{
	return make_number((AWKNUM) glutGetWindow());
}

NODE *
do_SetWindow(int nargs)
{
	NODE *tmp;
	int window;

	tmp    = (NODE *) get_scalar_argument(0, FALSE);
	window = (int) force_number(tmp);

	glutSetWindow(window);
	return make_number((AWKNUM) 0);
}

NODE *
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

NODE *
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

NODE *
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

NODE *
do_SetWindowTitle(int nargs)
{
	NODE *tmp;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);

	glutSetWindowTitle(tmp->stptr);
	return make_number((AWKNUM) 0);
}

NODE *
do_SetIconTitle(int nargs)
{
	NODE *tmp;

	tmp = (NODE*) get_actual_argument(0, FALSE, FALSE);
	force_string(tmp);

	glutSetIconTitle(tmp->stptr);
	return make_number((AWKNUM) 0);
}

NODE *
do_ShowWindow(int nargs)
{
	glutShowWindow();
	return make_number((AWKNUM) 0);
}

NODE *
do_HideWindow(int nargs)
{
	glutHideWindow();
	return make_number((AWKNUM) 0);
}

NODE *
do_IconifyWindow(int nargs)
{
	glutIconifyWindow();
	return make_number((AWKNUM) 0);
}

NODE *
do_PushWindow(int nargs)
{
	glutPushWindow();
	return make_number((AWKNUM) 0);
}

NODE *
do_PopWindow(int nargs)
{
	glutPopWindow();
	return make_number((AWKNUM) 0);
}

NODE *
do_FullScreen(int nargs)
{
	glutFullScreen();
	return make_number((AWKNUM) 0);
}

#if 0
NODE *
do_LeaveFullScreen(int nargs)
{
#ifdef HAVE_FREEGLUT
	glutLeaveFullScreen();
#endif
	return make_number((AWKNUM) 0);
}
#endif

NODE *
do_FullScreenToggle(int nargs)
{
#ifdef HAVE_FREEGLUT
	glutFullScreenToggle();
#else
	// TODO;
#endif
	return make_number((AWKNUM) 0);
}

#if 0
NODE *
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
#endif

NODE *
do_ReshapeFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Reshape_user_func = func_ptr;

	glutReshapeFunc(AgReshape);
	return make_number((AWKNUM) 0);
}

void
AgReshape(int w, int h)
{
	NODE *args[3];

	args[0] = make_number((AWKNUM) w);
	args[1] = make_number((AWKNUM) h);
	args[2] = NULL;

	callback_user_func(Reshape_user_func, args, 2);
	return;
}

#ifdef HAVE_FREEGLUT
void
AgClose(void)
{
	NODE *args[1];

	args[0] = NULL;

	callback_user_func(Close_user_func, args, 0);

	return;
}

void
AgWMClose(void)
{
	NODE *args[1];

	args[0] = NULL;

	callback_user_func(WMClose_user_func, args, 0);

	return;
}
#endif
