#include "dw4/reflected.h"
extern igMetaObject *g_igModelViewMatrixAttrList_metaObject[4];
extern "C" {
void FUN_00135620(void);
igMetaObject *igModelViewMatrixAttrList_GetMetaObject(void);
}
igMetaObject *igModelViewMatrixAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixAttrList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00135620();
    return g_igModelViewMatrixAttrList_metaObject[0];
}
