#include "dw4/reflected.h"
extern igMetaObject *g_igBoxComponent_metaObject[4];
extern "C" {
void igBoxComponent_RunStaticInit(void);
igMetaObject *igBoxComponent_GetMetaObject(void);
}
igMetaObject *igBoxComponent_GetMetaObject(void)
{
    igMetaObject *g = g_igBoxComponent_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igBoxComponent_RunStaticInit();
    return g_igBoxComponent_metaObject[0];
}
