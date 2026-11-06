#include "dw4/reflected.h"
extern "C" {
extern int g_igCriMovieData_metaObject[4];
int Gap__Core__igObject__vfunc_11();

/* Reset step: runs the igObject base step, then clears the three middleware handles the object
 * holds (_mwply, _adxt, _macroFunction; +8/+16/+24). */
void Gap__igCriMovieData__vfunc_11(igCriMovieData *self) {
    Gap__Core__igObject__vfunc_11();
    self->_mwply = 0;
    self->_adxt = 0;
    self->_macroFunction = 0;
}

int Gap__igCriMovieData__vfunc_20(void)
{
    return g_igCriMovieData_metaObject[0];
}
}
