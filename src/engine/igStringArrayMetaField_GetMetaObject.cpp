#include "dw4/reflected.h"
extern igMetaObject *g_igStringArrayMetaField_metaObject[4];
extern "C" {
void FUN_002b9d80(void);
igMetaObject *igStringArrayMetaField_GetMetaObject(void);
}
igMetaObject *igStringArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igStringArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b9d80();
    return g_igStringArrayMetaField_metaObject[0];
}
