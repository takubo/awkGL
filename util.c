/*
 * util.c
 */

#include "awkgl.h"

NODE *do_pi(int);
NODE *do_d2r(int);
NODE *do_r2d(int);

NODE *
do_pi(int nargs)
{
	if (do_lint && get_curfunc_arg_count() > 0)
		lintwarn("pi: called with too many arguments");

	return make_number((AWKNUM) M_PI);
}

NODE *
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
		return make_number((AWKNUM) 0); /* suppress warning */
	}
}

NODE *
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
		return make_number((AWKNUM) 0); /* suppress warning */
	}
}
