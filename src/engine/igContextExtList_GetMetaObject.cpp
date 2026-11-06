#include "dw4/reflected.h"
extern igMetaObject *g_igContextExtList_metaObject[4];
extern "C" {
void FUN_002cb420(void);
igMetaObject *igContextExtList_GetMetaObject(void);
}
igMetaObject *igContextExtList_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExtList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cb420();
    return g_igContextExtList_metaObject[0];
}
