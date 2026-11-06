#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2LongTimer_metaObject[4];
extern "C" {
void FUN_002cfd70(void);
igMetaObject *igPsx2LongTimer_GetMetaObject(void);
}
igMetaObject *igPsx2LongTimer_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2LongTimer_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002cfd70();
    return g_igPsx2LongTimer_metaObject[0];
}
