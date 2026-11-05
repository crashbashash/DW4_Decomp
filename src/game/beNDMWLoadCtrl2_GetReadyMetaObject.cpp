#include "dw4/reflected.h"
extern igMetaObject *DAT_0058bef0[4];
extern "C" {
void FUN_003c7ef0(void);
igMetaObject *beNDMWLoadCtrl2_GetReadyMetaObject(void);
}
igMetaObject *beNDMWLoadCtrl2_GetReadyMetaObject(void)
{
    igMetaObject *g = DAT_0058bef0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003c7ef0();
    return DAT_0058bef0[0];
}
