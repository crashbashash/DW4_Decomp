/* MERGED DRAFT: src/movie/igCriMovieCodec.c folded into src/movie/igCriMovieCodec.cpp (both are the same class; the C unit's functions carry retail exception records, so the class is one C++ translation unit).
 * Functions in retail address order follow; the two header blocks are kept as-is. */
/* src/movie/igCriMovieCodec.cpp — the igCriMovieCodec methods
 *
 * One translation unit: 1 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
extern "C" {
void Gap__Core__igObject__vfunc_02(void);
void Gap__igCriMovieCodec__vfunc_02(void);
}

/* 0x00337bf0 */
void Gap__igCriMovieCodec__vfunc_02(void)
{
    Gap__Core__igObject__vfunc_02();
}

/* ---- from src/movie/igCriMovieCodec.c ---- */
/* src/movie/igCriMovieCodec.c — the igCriMovieCodec methods
 *
 * One translation unit: 3 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern "C" {
extern int g_igCriMovieCodec_metaObject[4];
int FUN_002934c0(int (*)(), int (*)(), igCriMovieCodec *);
int Gap__Core__igObject__vfunc_01();
int FUN_00338d60();
int FUN_00338df0();

/* 0x00337bb0
 * Slot 1: run the igObject base step, then hand FUN_002934c0 a pair of
 * callbacks (0x00338d60, 0x00338df0) with the codec as their context.
 * FUN_002934c0 stores the two function pointers and the context in a record
 * from FUN_00294a30 (asm/FUN_002934c0.s: record+0x28, +0x2c, +0x30).
 * 0x00338d60 forwards its second argument to vtable slot 54 of the object
 * returned by 0x00301000. */
void Gap__igCriMovieCodec__vfunc_01(igCriMovieCodec *self) {
    Gap__Core__igObject__vfunc_01();
    FUN_002934c0(&FUN_00338d60, &FUN_00338df0, self);
}

/* 0x00337c10 — slot 21: returns 1 where the igMovieCodec base version
 * (0x00338ed0) returns 0. */
int Gap__igCriMovieCodec__vfunc_21(void)
{
    return 1;
}

/* 0x00338e30 — class MetaObject accessor: slot 0 of the published
 * igCriMovieCodec MetaObject handle at 0x587740. */
int Gap__igCriMovieCodec__vfunc_20(void)
{
    return g_igCriMovieCodec_metaObject[0];
}
}
