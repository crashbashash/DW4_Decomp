#include "dw4/reflected.h"
extern igMetaObject *g_igEventProducerList_metaObject[4];
extern "C" {
void FUN_00146190(void);
igMetaObject *igEventProducerList_GetMetaObject(void);
}
igMetaObject *igEventProducerList_GetMetaObject(void)
{
    igMetaObject *g = g_igEventProducerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146190();
    return g_igEventProducerList_metaObject[0];
}
