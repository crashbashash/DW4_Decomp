#include "dw4/reflected.h"
extern igMetaObject *g_igBitmapFont_metaObject[4];
extern "C" {
void igBitmapFont_RunStaticInit(void);
igMetaObject *igBitmapFont_GetMetaObject(void);
}
igMetaObject *igBitmapFont_GetMetaObject(void)
{
    igMetaObject *g = g_igBitmapFont_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igBitmapFont_RunStaticInit();
    return g_igBitmapFont_metaObject[0];
}
