#include "dw4/reflected.h"
extern igMetaObject *DAT_0058bfe8[4];
extern "C" {
void FUN_003c98f0(void);
igMetaObject *beNDMWShinkaObjectList_ResolveMetaObject(void);
}
igMetaObject *beNDMWShinkaObjectList_ResolveMetaObject(void)
{
    igMetaObject *g = DAT_0058bfe8[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003c98f0();
    return DAT_0058bfe8[0];
}
