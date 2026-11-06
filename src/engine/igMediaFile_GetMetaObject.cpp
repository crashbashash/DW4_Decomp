#include "dw4/reflected.h"
extern igMetaObject *g_igMediaFile_metaObject[4];
extern "C" {
void FUN_002c1430(void);
igMetaObject *igMediaFile_GetMetaObject(void);
}
igMetaObject *igMediaFile_GetMetaObject(void)
{
    igMetaObject *g = g_igMediaFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c1430();
    return g_igMediaFile_metaObject[0];
}
