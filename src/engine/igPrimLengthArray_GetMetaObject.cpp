#include "dw4/reflected.h"
extern igMetaObject *g_igPrimLengthArray_metaObject[4];
extern "C" {
void FUN_0014c0d0(void);
igMetaObject *igPrimLengthArray_GetMetaObject(void);
}
igMetaObject *igPrimLengthArray_GetMetaObject(void)
{
    igMetaObject *g = g_igPrimLengthArray_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014c0d0();
    return g_igPrimLengthArray_metaObject[0];
}
