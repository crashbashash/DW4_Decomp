#include "dw4/reflected.h"
extern igMetaObject *g_igFileImagePng_metaObject[4];
extern "C" {
void FUN_00150570(void);
igMetaObject *igFileImagePng_GetMetaObject(void);
}
igMetaObject *igFileImagePng_GetMetaObject(void)
{
    igMetaObject *g = g_igFileImagePng_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00150570();
    return g_igFileImagePng_metaObject[0];
}
