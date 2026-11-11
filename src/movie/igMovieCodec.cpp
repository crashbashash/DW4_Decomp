
typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;
extern "C" int FUN_00100610(void **);
extern "C" int igObject_Destroy(S_temp_a0 *);
extern "C" void **FUN_00338e50(void **arg0, short arg1);
extern "C" int g_igMovieCodec_metaObject[4];
extern "C" int Gap__igMovieCodec__vfunc_21(void);
extern "C" void Gap__igMovieCodec__vfunc_22(void);
extern "C" int Gap__igMovieCodec__vfunc_23(void);
extern "C" int Gap__igMovieCodec__vfunc_24(void);
extern "C" int Gap__igMovieCodec__vfunc_25(void);
extern "C" int Gap__igMovieCodec__vfunc_26(void);
extern "C" int Gap__igMovieCodec__vfunc_27(void);
extern "C" int Gap__igMovieCodec__vfunc_28(void);
extern "C" int Gap__igMovieCodec__vfunc_29(void);
extern "C" int Gap__igMovieCodec__vfunc_20(void);

void **FUN_00338e50(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

/* The igMovieCodec base class declares slots 21-29 as default bodies: every
 * one returns 0 (slot 22 returns nothing), and the concrete codec
 * (igCriMovieCodec) overrides the ones it supports, e.g. slot 21 -> 1. */

int Gap__igMovieCodec__vfunc_21(void) {
    return 0;
}

void Gap__igMovieCodec__vfunc_22(void)
{
}

int Gap__igMovieCodec__vfunc_23(void) {
    return 0;
}

int Gap__igMovieCodec__vfunc_24(void) {
    return 0;
}

int Gap__igMovieCodec__vfunc_25(void) {
    return 0;
}

int Gap__igMovieCodec__vfunc_26(void) {
    return 0;
}

int Gap__igMovieCodec__vfunc_27(void) {
    return 0;
}

int Gap__igMovieCodec__vfunc_28(void) {
    return 0;
}

int Gap__igMovieCodec__vfunc_29(void) {
    return 0;
}

int Gap__igMovieCodec__vfunc_20(void)
{
    return g_igMovieCodec_metaObject[0];
}

