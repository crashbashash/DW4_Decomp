#include "dw4/reflected.h"
extern igMetaObject *g_igMetaFieldInfo_metaObject_00585cb8[4];
extern "C" {
void FUN_002bebb0(void);
igMetaObject *igMetaFieldInfo_GetMetaObject(void);
}
igMetaObject *igMetaFieldInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaFieldInfo_metaObject_00585cb8[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bebb0();
    return g_igMetaFieldInfo_metaObject_00585cb8[0];
}
