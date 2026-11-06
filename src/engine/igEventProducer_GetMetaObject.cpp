#include "dw4/reflected.h"
extern igMetaObject *g_igEventProducer_metaObject[4];
extern "C" {
void FUN_00146270(void);
igMetaObject *igEventProducer_GetMetaObject(void);
}
igMetaObject *igEventProducer_GetMetaObject(void)
{
    igMetaObject *g = g_igEventProducer_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00146270();
    return g_igEventProducer_metaObject[0];
}
