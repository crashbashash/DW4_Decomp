#include "dw4/reflected.h"
extern igMetaObject *g_igDriverDatabase_metaObject[4];
extern "C" {
void FUN_002c68f0(void);
igMetaObject *igDriverDatabase_GetMetaObject(void);
}
igMetaObject *igDriverDatabase_GetMetaObject(void)
{
    igMetaObject *g = g_igDriverDatabase_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c68f0();
    return g_igDriverDatabase_metaObject[0];
}
