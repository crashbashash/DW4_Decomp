#include "dw4/reflected.h"
extern igMetaObject *g_igCompressedTransformSequence1_5Data_metaObject[4];
extern "C" {
void FUN_001a2640(void);
igMetaObject *igCompressedTransformSequence1_5Data_GetMetaObject(void);
}
igMetaObject *igCompressedTransformSequence1_5Data_GetMetaObject(void)
{
    igMetaObject *g = g_igCompressedTransformSequence1_5Data_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a2640();
    return g_igCompressedTransformSequence1_5Data_metaObject[0];
}
