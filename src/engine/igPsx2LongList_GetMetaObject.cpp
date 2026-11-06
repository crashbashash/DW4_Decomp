#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2LongList_metaObject[4];
extern "C" {
void FUN_001528e0(void);
igMetaObject *igPsx2LongList_GetMetaObject(void);
}
igMetaObject *igPsx2LongList_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2LongList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001528e0();
    return g_igPsx2LongList_metaObject[0];
}
