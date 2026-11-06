#include "dw4/reflected.h"
extern igMetaObject *g_igMemoryRefArrayMetaField_metaObject_00585de0[4];
extern "C" {
void FUN_002bfb50(void);
igMetaObject *igMemoryRefArrayMetaField_GetMetaObject(void);
}
igMetaObject *igMemoryRefArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryRefArrayMetaField_metaObject_00585de0[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bfb50();
    return g_igMemoryRefArrayMetaField_metaObject_00585de0[0];
}
