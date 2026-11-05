#include "dw4/reflected.h"
extern igMetaObject *DAT_0058b800[4];
extern "C" {
void FUN_003c3300(void);
igMetaObject *beNDMWLoadIntf2Diffselect_ResolveMetaObject(void);
}
igMetaObject *beNDMWLoadIntf2Diffselect_ResolveMetaObject(void)
{
    igMetaObject *g = DAT_0058b800[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003c3300();
    return DAT_0058b800[0];
}
