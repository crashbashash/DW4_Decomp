#include "dw4/reflected.h"
extern igMetaObject *g_igBoxComponent_metaObject[4];
extern "C" {
void igBoxComponent_RunStaticInit(void);
igMetaObject *igBoxComponent_GetMetaObject(void);
}
igMetaObject *igBoxComponent_GetMetaObject(void)
{
    igMetaObject *g = g_igBoxComponent_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igBoxComponent_RunStaticInit();
    return g_igBoxComponent_metaObject[0];
}
