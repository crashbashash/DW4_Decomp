#include "dw4/reflected.h"
extern igMetaObject *DAT_0058bc98[4];
extern "C" {
void FUN_003c5bc0(void);
igMetaObject *beNDMWMcSlotXbox_GetReadyMetaObject(void);
}
igMetaObject *beNDMWMcSlotXbox_GetReadyMetaObject(void)
{
    igMetaObject *g = DAT_0058bc98[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003c5bc0();
    return DAT_0058bc98[0];
}
