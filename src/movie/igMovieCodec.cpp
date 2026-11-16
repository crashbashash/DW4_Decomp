
#include "dw4/igMovieCodec.h"
extern "C" int igMovieCodec_IsReusable(void);
extern "C" void igMovieCodec_Initialize(void);
extern "C" int igMovieCodec_Open(void);
extern "C" int igMovieCodec_Close(void);
extern "C" int igMovieCodec_Play(void);
extern "C" int igMovieCodec_Pause(void);
extern "C" int igMovieCodec_Update(void);
extern "C" int igMovieCodec_InitializeDrawing(void);
extern "C" int igMovieCodec_ReleaseDrawing(void);
extern "C" igMetaObject *igMovieCodec_GetMeta(void);

/* The igMovieCodec base class declares slots 21-29 as default bodies: every
 * one returns 0 (slot 22 returns nothing), and the concrete codec
 * (igCriMovieCodec) overrides the ones it supports, e.g. slot 21 -> 1. */

int igMovieCodec_IsReusable(void) {
    return 0;
}

void igMovieCodec_Initialize(void)
{
}

int igMovieCodec_Open(void) {
    return 0;
}

int igMovieCodec_Close(void) {
    return 0;
}

int igMovieCodec_Play(void) {
    return 0;
}

int igMovieCodec_Pause(void) {
    return 0;
}

int igMovieCodec_Update(void) {
    return 0;
}

int igMovieCodec_InitializeDrawing(void) {
    return 0;
}

int igMovieCodec_ReleaseDrawing(void) {
    return 0;
}

igMetaObject *igMovieCodec_GetMeta(void)
{
    return g_igMovieCodec_metaObject;
}

