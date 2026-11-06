#include "dw4/reflected.h"
extern igMetaObject *g_igBasicColorChanger_metaObject[4];
extern "C" {
void igBasicColorChanger_RunStaticInit(void);
igMetaObject *igBasicColorChanger_GetMetaObject(void);
}
igMetaObject *igBasicColorChanger_GetMetaObject(void)
{
    igMetaObject *g = g_igBasicColorChanger_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igBasicColorChanger_RunStaticInit();
    return g_igBasicColorChanger_metaObject[0];
}
