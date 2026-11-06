#include "dw4/reflected.h"
extern igMetaObject *g_igIGBFile_metaObject[4];
extern "C" {
void FUN_002c3de0(void);
igMetaObject *igIGBFile_GetMetaObject(void);
}
igMetaObject *igIGBFile_GetMetaObject(void)
{
    igMetaObject *g = g_igIGBFile_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c3de0();
    return g_igIGBFile_metaObject[0];
}
