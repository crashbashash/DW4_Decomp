extern "C" {
void Gap__Core__igObject__vfunc_02(void);
void Gap__igCriMovieCodec__vfunc_02(void);
}

void Gap__igCriMovieCodec__vfunc_02(void)
{
    Gap__Core__igObject__vfunc_02();
}

#include "dw4/reflected.h"
extern "C" {
extern int g_igCriMovieCodec_metaObject[4];
int FUN_002934c0(int (*)(), int (*)(), igCriMovieCodec *);
int Gap__Core__igObject__vfunc_01();
int FUN_00338d60();
int FUN_00338df0();

/* Runs the igObject base step, then hands FUN_002934c0 a pair of callbacks with the codec as their
 * context. FUN_002934c0 stores the two function pointers and the context in a record from
 * FUN_00294a30 (record+0x28, +0x2c, +0x30). The first callback forwards its second argument to
 * vtable slot 54 of the object returned by 0x00301000. */
void Gap__igCriMovieCodec__vfunc_01(igCriMovieCodec *self) {
    Gap__Core__igObject__vfunc_01();
    FUN_002934c0(&FUN_00338d60, &FUN_00338df0, self);
}

/* Returns 1 where the igMovieCodec base version returns 0. */
int Gap__igCriMovieCodec__vfunc_21(void)
{
    return 1;
}

int Gap__igCriMovieCodec__vfunc_20(void)
{
    return g_igCriMovieCodec_metaObject[0];
}
}
