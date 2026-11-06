#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2UserUCodeExt_metaObject[4];
extern "C" {
void FUN_00152d10(void);
igMetaObject *igPsx2UserUCodeExt_GetMetaObject(void);
}
igMetaObject *igPsx2UserUCodeExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2UserUCodeExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00152d10();
    return g_igPsx2UserUCodeExt_metaObject[0];
}
