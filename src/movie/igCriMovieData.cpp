/* src/movie/igCriMovieData.c — the igCriMovieData methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern "C" {
extern int g_igCriMovieData_metaObject_00587760[4];
/* igObject's vfunc 11 default: an empty body in retail (a bare `jr ra`). */
int Gap__Core__igObject__vfunc_11();

/* 0x00337b80
 * Reset step: run the igObject base step, then clear the three middleware handles the
 * object holds (_mwply, _adxt, _macroFunction; reflected field names, +8/+16/+24). */
void Gap__igCriMovieData__vfunc_11(igCriMovieData *self) {
    Gap__Core__igObject__vfunc_11();
    self->_mwply = 0;
    self->_adxt = 0;
    self->_macroFunction = 0;
}

/* 0x00338e40
 * Metaobject accessor: the class's metaobject handle at 0x00587760. */
int Gap__igCriMovieData__vfunc_20(void)
{
    return g_igCriMovieData_metaObject_00587760[0];
}
}
