#include "dw4/reflected.h"
extern igMetaObject *DAT_0058aec0[4];
extern "C" {
void FUN_003b9c20(void);
igMetaObject *FUN_003b9a90(void);
}
igMetaObject *FUN_003b9a90(void)
{
    igMetaObject *g = DAT_0058aec0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003b9c20();
    return DAT_0058aec0[0];
}
