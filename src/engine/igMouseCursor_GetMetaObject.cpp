#include "dw4/reflected.h"
extern igMetaObject *g_igMouseCursor_metaObject[4];
extern "C" {
void igMouseCursor_RunStaticInit(void);
igMetaObject *igMouseCursor_GetMetaObject(void);
}
igMetaObject *igMouseCursor_GetMetaObject(void)
{
    igMetaObject *g = g_igMouseCursor_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igMouseCursor_RunStaticInit();
    return g_igMouseCursor_metaObject[0];
}
