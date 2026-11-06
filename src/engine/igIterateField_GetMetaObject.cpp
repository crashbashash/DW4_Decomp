#include "dw4/reflected.h"
extern igMetaObject *g_igIterateField_metaObject[4];
extern "C" {
void FUN_002278a0(void);
igMetaObject *igIterateField_GetMetaObject(void);
}
igMetaObject *igIterateField_GetMetaObject(void)
{
    igMetaObject *g = g_igIterateField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002278a0();
    return g_igIterateField_metaObject[0];
}
