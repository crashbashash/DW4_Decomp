#include "dw4/reflected.h"
extern igMetaObject *g_igColorChanger_metaObject[4];
extern "C" {
void igColorChanger_RunStaticInit(void);
igMetaObject *igColorChanger_GetMetaObject(void);
}
igMetaObject *igColorChanger_GetMetaObject(void)
{
    igMetaObject *g = g_igColorChanger_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igColorChanger_RunStaticInit();
    return g_igColorChanger_metaObject[0];
}
