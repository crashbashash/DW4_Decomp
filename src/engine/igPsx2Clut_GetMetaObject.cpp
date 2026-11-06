#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2Clut_metaObject[4];
extern "C" {
void FUN_00154490(void);
igMetaObject *igPsx2Clut_GetMetaObject(void);
}
igMetaObject *igPsx2Clut_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Clut_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00154490();
    return g_igPsx2Clut_metaObject[0];
}
