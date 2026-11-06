#include "dw4/reflected.h"
extern igMetaObject *g_igCustomStateField_metaObject[4];
extern "C" {
void FUN_0014ecd0(void);
igMetaObject *igCustomStateField_GetMetaObject(void);
}
igMetaObject *igCustomStateField_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomStateField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014ecd0();
    return g_igCustomStateField_metaObject[0];
}
