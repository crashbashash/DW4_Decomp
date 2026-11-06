#include "dw4/reflected.h"
extern igMetaObject *g_igModel_metaObject[4];
extern "C" {
void igModel_RunStaticInit(void);
igMetaObject *igModel_GetMetaObject(void);
}
igMetaObject *igModel_GetMetaObject(void)
{
    igMetaObject *g = g_igModel_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igModel_RunStaticInit();
    return g_igModel_metaObject[0];
}
