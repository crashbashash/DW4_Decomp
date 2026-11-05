#include "dw4/reflected.h"
extern igMetaObject *DAT_00587740[4];
extern "C" {
void FUN_003359b0(void);
igMetaObject *FUN_00335850(void);
}
igMetaObject *FUN_00335850(void)
{
    igMetaObject *g = DAT_00587740[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003359b0();
    return DAT_00587740[0];
}
