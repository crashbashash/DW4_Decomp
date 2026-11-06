#include "dw4/reflected.h"
extern igMetaObject *g_igOnOffModel_metaObject[4];
extern "C" {
void igOnOffModel_RunStaticInit(void);
igMetaObject *igOnOffModel_GetMetaObject(void);
}
igMetaObject *igOnOffModel_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffModel_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffModel_RunStaticInit();
    return g_igOnOffModel_metaObject[0];
}
