#include "dw4/reflected.h"
extern igMetaObject *g_igMouseCursor_metaObject[4];
extern "C" {
void igMouseCursor_RunStaticInit(void);
igMetaObject *igMouseCursor_GetMetaObject(void);
}
igMetaObject *igMouseCursor_GetMetaObject(void)
{
    igMetaObject *g = g_igMouseCursor_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMouseCursor_RunStaticInit();
    return g_igMouseCursor_metaObject[0];
}
