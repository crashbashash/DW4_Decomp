#include "dw4/reflected.h"
extern igMetaObject *g_igAppearanceList_metaObject[4];
extern "C" {
void FUN_001a60c0(void);
igMetaObject *igAppearanceList_GetMetaObject(void);
}
igMetaObject *igAppearanceList_GetMetaObject(void)
{
    igMetaObject *g = g_igAppearanceList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a60c0();
    return g_igAppearanceList_metaObject[0];
}
