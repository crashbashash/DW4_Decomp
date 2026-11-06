#include "dw4/reflected.h"
extern "C" {
void FUN_0033bbd0(int);
void Gap__igMovieRenderer__vfunc_24(igMovieRenderer *);
}
extern "C" {
void FUN_00339200(int);
void Gap__igMovieRenderer__vfunc_22(igMovieRenderer *);
}

/* Forwards to FUN_0033bbd0 with the renderer's movie manager (_movieManager, +12). The helper
 * walks the manager's movie list (+16) and calls virtual slot 29 on the object held at +72 of each
 * entry. */
void Gap__igMovieRenderer__vfunc_24(igMovieRenderer *self)
{
    FUN_0033bbd0(self->_movieManager);
}

/* The same walk as slot 24 through FUN_00339200, which calls virtual slot 31 instead of slot 29 on
 * each entry's +72 object. */
void Gap__igMovieRenderer__vfunc_22(igMovieRenderer *self)
{
    FUN_00339200(self->_movieManager);
}
