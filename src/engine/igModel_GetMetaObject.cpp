#include "dw4/reflected.h"
extern igMetaObject *g_igModel_metaObject[4];
extern "C" {
void igModel_RunStaticInit(void);
igMetaObject *igModel_GetMetaObject(void);
}
igMetaObject *igModel_GetMetaObject(void)
{
    igMetaObject *g = g_igModel_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igModel_RunStaticInit();
    return g_igModel_metaObject[0];
}
