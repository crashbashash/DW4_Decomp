#include "dw4/reflected.h"
extern igMetaObject *g_igEventProducer_metaObject[4];
extern "C" {
void FUN_00146270(void);
igMetaObject *igEventProducer_GetMetaObject(void);
}
igMetaObject *igEventProducer_GetMetaObject(void)
{
    igMetaObject *g = g_igEventProducer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146270();
    return g_igEventProducer_metaObject[0];
}
