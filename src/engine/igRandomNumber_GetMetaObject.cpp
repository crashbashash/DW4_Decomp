#include "dw4/reflected.h"
extern igMetaObject *g_igRandomNumber_metaObject[4];
extern "C" {
void FUN_001e42e0(void);
igMetaObject *igRandomNumber_GetMetaObject(void);
}
igMetaObject *igRandomNumber_GetMetaObject(void)
{
    igMetaObject *g = g_igRandomNumber_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e42e0();
    return g_igRandomNumber_metaObject[0];
}
