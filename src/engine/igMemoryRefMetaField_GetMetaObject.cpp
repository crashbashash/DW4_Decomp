#include "dw4/reflected.h"
extern igMetaObject *g_igMemoryRefMetaField_metaObject[4];
extern "C" {
void igMemoryRefMetaField_EnsureRegistered(void);
igMetaObject *igMemoryRefMetaField_GetMetaObject(void);
}
igMetaObject *igMemoryRefMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryRefMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryRefMetaField_EnsureRegistered();
    return g_igMemoryRefMetaField_metaObject[0];
}
