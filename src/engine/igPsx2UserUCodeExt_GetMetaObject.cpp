#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2UserUCodeExt_metaObject[4];
extern "C" {
void FUN_00152d10(void);
igMetaObject *igPsx2UserUCodeExt_GetMetaObject(void);
}
igMetaObject *igPsx2UserUCodeExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2UserUCodeExt_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00152d10();
    return g_igPsx2UserUCodeExt_metaObject[0];
}
