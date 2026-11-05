/* src/movie/igMovieCodec.c — the igMovieCodec methods
 *
 * One translation unit: 10 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */

extern int g_igMovieCodec_metaObject_00587738[4];

/* The igMovieCodec base class declares slots 21-29 as default bodies: every
 * one returns 0 (slot 22 returns nothing), and the concrete codec
 * (igCriMovieCodec) overrides the ones it supports, e.g. slot 21 -> 1. */

/* 0x00338ed0 */
int Gap__igMovieCodec__vfunc_21(void) {
    return 0;
}

/* 0x00338ee0 */
void Gap__igMovieCodec__vfunc_22(void)
{
}

/* 0x00338ef0 */
int Gap__igMovieCodec__vfunc_23(void) {
    return 0;
}

/* 0x00338f00 */
int Gap__igMovieCodec__vfunc_24(void) {
    return 0;
}

/* 0x00338f10 */
int Gap__igMovieCodec__vfunc_25(void) {
    return 0;
}

/* 0x00338f20 */
int Gap__igMovieCodec__vfunc_26(void) {
    return 0;
}

/* 0x00338f30 */
int Gap__igMovieCodec__vfunc_27(void) {
    return 0;
}

/* 0x00338f40 */
int Gap__igMovieCodec__vfunc_28(void) {
    return 0;
}

/* 0x00338f50 */
int Gap__igMovieCodec__vfunc_29(void) {
    return 0;
}

/* 0x00338f60 — class MetaObject accessor: slot 0 of the published
 * igMovieCodec MetaObject handle at 0x587738. */
int Gap__igMovieCodec__vfunc_20(void)
{
    return g_igMovieCodec_metaObject_00587738[0];
}
