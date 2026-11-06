#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2ScissorExt_metaObject[4];
extern "C" {
void FUN_00153000(void);
igMetaObject *igPsx2ScissorExt_GetMetaObject(void);
}
igMetaObject *igPsx2ScissorExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ScissorExt_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00153000();
    return g_igPsx2ScissorExt_metaObject[0];
}
