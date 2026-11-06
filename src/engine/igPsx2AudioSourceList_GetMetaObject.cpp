#include "dw4/meta_object.h"
extern igMetaObject *g_igPsx2AudioSourceList_metaObject[4];
extern "C" {
void FUN_00143690(void);
igMetaObject *igPsx2AudioSourceList_GetMetaObject(void);
}
igMetaObject *igPsx2AudioSourceList_GetMetaObject(void)
{
    if (g_igPsx2AudioSourceList_metaObject[0] == 0 || igMetaObject_IsRegistered(g_igPsx2AudioSourceList_metaObject[0]) == false)
        FUN_00143690();
    return g_igPsx2AudioSourceList_metaObject[0];
}
