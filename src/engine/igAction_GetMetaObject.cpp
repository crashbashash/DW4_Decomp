#include "dw4/reflected.h"
extern igMetaObject *g_igAction_metaObject[4];
extern "C" {
void igAction_RunStaticInit(void);
igMetaObject *igAction_GetMetaObject(void);
}
igMetaObject *igAction_GetMetaObject(void)
{
    igMetaObject *g = g_igAction_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igAction_RunStaticInit();
    return g_igAction_metaObject[0];
}
