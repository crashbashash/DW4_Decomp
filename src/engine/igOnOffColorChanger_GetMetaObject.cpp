#include "dw4/reflected.h"
extern igMetaObject *g_igOnOffColorChanger_metaObject[4];
extern "C" {
void igOnOffColorChanger_RunStaticInit(void);
igMetaObject *igOnOffColorChanger_GetMetaObject(void);
}
igMetaObject *igOnOffColorChanger_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffColorChanger_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffColorChanger_RunStaticInit();
    return g_igOnOffColorChanger_metaObject[0];
}
