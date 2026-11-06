#include "dw4/reflected.h"
extern igMetaObject *g_igAABox_metaObject[4];
extern "C" {
void FUN_0018a780(void);
igMetaObject *igAABox_GetMetaObject(void);
}
igMetaObject *igAABox_GetMetaObject(void)
{
    igMetaObject *g = g_igAABox_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0018a780();
    return g_igAABox_metaObject[0];
}
