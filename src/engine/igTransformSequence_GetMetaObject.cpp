#include "dw4/reflected.h"
extern igMetaObject *g_igTransformSequence_metaObject[4];
extern "C" {
void FUN_00195580(void);
igMetaObject *igTransformSequence_GetMetaObject(void);
}
igMetaObject *igTransformSequence_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformSequence_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00195580();
    return g_igTransformSequence_metaObject[0];
}
