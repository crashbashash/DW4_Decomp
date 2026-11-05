/* src/movie/igMovieRenderer.cpp — the igMovieRenderer methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern "C" {
void FUN_0033bbd0(int);
void Gap__igMovieRenderer__vfunc_24(igMovieRenderer *);
}
extern "C" {
void FUN_00339200(int);
void Gap__igMovieRenderer__vfunc_22(igMovieRenderer *);
}

/* 0x0033be00 - slot 24: forward to FUN_0033bbd0 with the renderer's movie
 * manager (_movieManager, +12).  Asm: the helper walks the manager's movie
 * list (+16) and calls virtual slot 29 on the object held at +72 of each
 * entry. */
void Gap__igMovieRenderer__vfunc_24(igMovieRenderer *self)
{
    FUN_0033bbd0(self->_movieManager);
}

/* 0x0033be20 - slot 22: the same walk as slot 24 through FUN_00339200, which
 * calls virtual slot 31 instead of slot 29 on each entry's +72 object. */
void Gap__igMovieRenderer__vfunc_22(igMovieRenderer *self)
{
    FUN_00339200(self->_movieManager);
}
