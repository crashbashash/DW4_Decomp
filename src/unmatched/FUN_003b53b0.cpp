#include "dw4/reflected.h"
extern igMetaObject *DAT_0058abe0[4];
extern "C" {
void FUN_003b5480(void);
igMetaObject *FUN_003b53b0(void);
}
igMetaObject *FUN_003b53b0(void)
{
    igMetaObject *g = DAT_0058abe0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003b5480();
    return DAT_0058abe0[0];
}
