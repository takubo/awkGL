/*
 * loop.c
 */

#include "awkgl.h"

NODE *Display_user_func = NULL;
NODE *Idle_user_func = NULL;
NODE *Timer_user_func = NULL;

NODE *do_MainLoop(int);
NODE *do_MainLoopEvent(int);
NODE *do_LeaveMainLoop(int);
NODE *do_Exit(int);

NODE *do_DisplayFunc(int);
NODE *do_IdleFunc(int);
NODE *do_TimerFunc(int);

NODE *do_PostRedisplay(int);
NODE *do_PostWindowRedisplay(int);

void AgDisplay(void);
void AgIdle(void);
void AgTimer(int);

NODE *
do_MainLoop(int nargs)
{
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
	// OpenGLでは、GL_LIGHT0 - GL_LIGHT7の８つの光源は最低使え、
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

NODE *
do_MainLoopEvent(int nargs)
{
#ifdef HAVE_FREEGLUT
	glutMainLoopEvent();
#endif
	return make_number((AWKNUM) 0);
}

NODE *
do_LeaveMainLoop(int nargs)
{
#ifdef HAVE_FREEGLUT
	glutLeaveMainLoop();
#endif
	return make_number((AWKNUM) 0);
}

NODE *
do_Exit(int nargs)
{
#ifdef HAVE_FREEGLUT
	glutExit();
#endif
	return make_number((AWKNUM) 0);
}

NODE *
do_DisplayFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Display_user_func = func_ptr;

	glutDisplayFunc(AgDisplay);
	return make_number((AWKNUM) 0);
}

NODE *
do_IdleFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Idle_user_func = func_ptr;

	glutIdleFunc(AgIdle);
	return make_number((AWKNUM) 0);
}

//void glutTimerFunc(unsigned int msecs, void (*func)(int value), value);
NODE *
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

NODE *
do_PostRedisplay(int nargs)
{
	glutPostRedisplay();
	return make_number((AWKNUM) 0);
}

NODE *
do_PostWindowRedisplay(int nargs)
{
	NODE *tmp;
	int window;

	tmp    = (NODE*) get_scalar_argument(0, FALSE);
	window = (int) force_number(tmp);

	glutPostWindowRedisplay(window );
	return make_number((AWKNUM) 0);
}

void
AgDisplay(void)
{
	NODE *args[1];

	args[0] = NULL;

	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	callback_user_func(Display_user_func, args, 0);
	glDisable(GL_DEPTH_TEST);

	//glFlush();
	glutSwapBuffers();
}

void
AgIdle(void)
{
	NODE *args[1];

	args[0] = NULL;

	callback_user_func(Idle_user_func, args, 0);
	return;
}

void
AgTimer(int value)
{
	NODE *args[2];

	args[0] = make_number((AWKNUM) value);
	args[1] = NULL;

	callback_user_func(Timer_user_func, args, 1);
	glutPostRedisplay();
	return;
}
