#include "dw4/reflected.h"
extern igMetaObject *DAT_0058ce18[4];
extern "C" {
void FUN_0045e050(void);
igMetaObject *igBoundingBoxRenderer_GetMetaObject(void);
}
igMetaObject *igBoundingBoxRenderer_GetMetaObject(void)
{
    igMetaObject *g = DAT_0058ce18[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0045e050();
    return DAT_0058ce18[0];
}
