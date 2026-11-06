#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2IndexArray_metaObject[4];
extern "C" {
void FUN_00153b40(void);
igMetaObject *igPsx2IndexArray_GetMetaObject(void);
}
igMetaObject *igPsx2IndexArray_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2IndexArray_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00153b40();
    return g_igPsx2IndexArray_metaObject[0];
}
