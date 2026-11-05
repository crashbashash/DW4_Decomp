#include "dw4/reflected.h"
extern igMetaObject *DAT_0058b4a0[4];
extern "C" {
void FUN_003c1070(void);
igMetaObject *beNDMWMdlMapBase_GetReadyMetaObject(void);
}
igMetaObject *beNDMWMdlMapBase_GetReadyMetaObject(void)
{
    igMetaObject *g = DAT_0058b4a0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003c1070();
    return DAT_0058b4a0[0];
}
