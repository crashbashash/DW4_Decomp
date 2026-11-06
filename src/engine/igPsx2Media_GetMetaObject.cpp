#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2Media_metaObject[4];
extern "C" {
void FUN_002cfac0(void);
igMetaObject *igPsx2Media_GetMetaObject(void);
}
igMetaObject *igPsx2Media_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Media_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002cfac0();
    return g_igPsx2Media_metaObject[0];
}
