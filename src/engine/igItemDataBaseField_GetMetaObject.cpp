#include "dw4/reflected.h"
extern igMetaObject *g_igItemDataBaseField_metaObject[4];
extern "C" {
void FUN_00228410(void);
igMetaObject *igItemDataBaseField_GetMetaObject(void);
}
igMetaObject *igItemDataBaseField_GetMetaObject(void)
{
    igMetaObject *g = g_igItemDataBaseField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00228410();
    return g_igItemDataBaseField_metaObject[0];
}
