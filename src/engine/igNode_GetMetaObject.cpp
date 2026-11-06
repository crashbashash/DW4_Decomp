#include "dw4/reflected.h"
extern igMetaObject *g_igNode_metaObject[4];
extern "C" {
void FUN_0019cf10(void);
igMetaObject *igNode_GetMetaObject(void);
}
igMetaObject *igNode_GetMetaObject(void)
{
    igMetaObject *g = g_igNode_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019cf10();
    return g_igNode_metaObject[0];
}
