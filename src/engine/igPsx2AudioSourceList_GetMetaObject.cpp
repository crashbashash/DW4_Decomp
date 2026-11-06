#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2AudioSourceList_metaObject[4];
extern "C" {
void FUN_00143690(void);
igMetaObject *igPsx2AudioSourceList_GetMetaObject(void);
}
igMetaObject *igPsx2AudioSourceList_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2AudioSourceList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00143690();
    return g_igPsx2AudioSourceList_metaObject[0];
}
