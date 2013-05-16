/*
 * device.c
 */

#include "awkgl.h"

NODE *Keyboard_user_func = NULL;
NODE *KeyboardUp_user_func = NULL;
NODE *Special_user_func = NULL;
NODE *SpecialUp_user_func = NULL;
NODE *Mouse_user_func = NULL;
NODE *Motion_user_func = NULL;
NODE *PassiveMotion_user_func = NULL;
#ifdef HAVE_FREEGLUT
NODE *MouseWheel_user_func = NULL;
#endif
NODE *Entry_user_func = NULL;

NODE *do_KeyboardFunc(int);
NODE *do_KeyboardUpFunc(int);
NODE *do_SpecialFunc(int);
NODE *do_SpecialUpFunc(int);
NODE *do_MouseFunc(int);
NODE *do_MotionFunc(int);
NODE *do_PassiveMotionFunc(int);
NODE *do_GetModifiers(int);
#ifdef HAVE_FREEGLUT
NODE *do_MouseWheelFunc(int);
#endif
NODE *do_EntryFunc(int);

void AgKeyboard(unsigned char, int, int);
void AgKeyboardUp(unsigned char, int, int);
void AgSpecial(int, int, int);
void AgSpecialUp(int, int, int);
static const char *specialkey2str(int);
void AgMouse(int, int, int, int);
void AgMotion(int, int);
void AgPassiveMotion(int, int);
#ifdef HAVE_FREEGLUT
void AgMouseWheel(int, int, int, int);
#endif
void AgEntry(int);

NODE *
do_KeyboardFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Keyboard_user_func = func_ptr;

	glutKeyboardFunc(AgKeyboard);
	return make_number((AWKNUM) 0);
}

NODE *
do_KeyboardUpFunc(int nargs)
{
	NODE *func_ptr = user_func();
	KeyboardUp_user_func = func_ptr;

	glutKeyboardUpFunc(AgKeyboardUp);
	return make_number((AWKNUM) 0);
}

NODE *
do_SpecialFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Special_user_func = func_ptr;

	glutSpecialFunc(AgSpecial);
	return make_number((AWKNUM) 0);
}

NODE *
do_SpecialUpFunc(int nargs)
{
	NODE *func_ptr = user_func();
	SpecialUp_user_func = func_ptr;

	glutSpecialUpFunc(AgSpecialUp);
	return make_number((AWKNUM) 0);
}

NODE *
do_MouseFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Mouse_user_func = func_ptr;

	glutMouseFunc(AgMouse);
	return make_number((AWKNUM) 0);
}

NODE *
do_MotionFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Motion_user_func = func_ptr;

	glutMotionFunc(AgMotion);
	return make_number((AWKNUM) 0);
}

NODE *
do_PassiveMotionFunc(int nargs)
{
	NODE *func_ptr = user_func();
	PassiveMotion_user_func = func_ptr;

	glutPassiveMotionFunc(AgPassiveMotion);
	return make_number((AWKNUM) 0);
}

NODE *
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

#ifdef HAVE_FREEGLUT
NODE *
do_MouseWheelFunc(int nargs)
{
	NODE *func_ptr = user_func();
	MouseWheel_user_func = func_ptr;

	glutMouseWheelFunc(AgMouseWheel);
	return make_number((AWKNUM) 0);
}
#endif

NODE *
do_EntryFunc(int nargs)
{
	NODE *func_ptr = user_func();
	Entry_user_func = func_ptr;

	glutEntryFunc(AgEntry);
	return make_number((AWKNUM) 0);
}

void
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

void
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

void
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

void
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

void
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
	default:
	    stt_str = ""; /* suppress warning */
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

void
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

void
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

#ifdef HAVE_FREEGLUT
void
AgMouseWheel(int wheel, int direction, int x, int y)
{
	NODE *args[5];

	args[0] = make_number((AWKNUM) wheel);
	args[1] = make_number((AWKNUM) direction);
	args[2] = make_number((AWKNUM) x);
	args[3] = make_number((AWKNUM) y);
	args[4] = NULL;

	callback_user_func(MouseWheel_user_func, args, 4);

	glutPostRedisplay();
	return;
}
#endif

void
AgEntry(int state)
{
	NODE *args[2];

	args[0] = make_number((AWKNUM) state);
	args[1] = NULL;

	callback_user_func(Entry_user_func, args, 2);
	return;
}
