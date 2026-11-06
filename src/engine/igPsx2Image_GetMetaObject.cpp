#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2Image_metaObject[4];
extern "C" {
void FUN_00153e60(void);
igMetaObject *igPsx2Image_GetMetaObject(void);
}
igMetaObject *igPsx2Image_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Image_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00153e60();
    return g_igPsx2Image_metaObject[0];
}
