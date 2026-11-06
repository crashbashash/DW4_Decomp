#include "dw4/reflected.h"
extern igMetaObject *g_igCharArrayMetaField_metaObject[4];
extern "C" {
void FUN_002cc420(void);
igMetaObject *igCharArrayMetaField_GetMetaObject(void);
}
igMetaObject *igCharArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCharArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cc420();
    return g_igCharArrayMetaField_metaObject[0];
}
