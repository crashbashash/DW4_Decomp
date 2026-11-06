#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2ImageConvert_metaObject[4];
extern "C" {
void FUN_00153c80(void);
igMetaObject *igPsx2ImageConvert_GetMetaObject(void);
}
igMetaObject *igPsx2ImageConvert_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ImageConvert_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00153c80();
    return g_igPsx2ImageConvert_metaObject[0];
}
