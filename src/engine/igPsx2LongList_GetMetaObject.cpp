#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2LongList_metaObject[4];
extern "C" {
void FUN_001528e0(void);
igMetaObject *igPsx2LongList_GetMetaObject(void);
}
igMetaObject *igPsx2LongList_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2LongList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001528e0();
    return g_igPsx2LongList_metaObject[0];
}
