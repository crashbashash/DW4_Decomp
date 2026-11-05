#include "dw4/reflected.h"
extern igMetaObject *DAT_005891c0[4];
extern "C" {
void FUN_0035ae60(void);
igMetaObject *FUN_0035ad10(void);
}
igMetaObject *FUN_0035ad10(void)
{
    igMetaObject *g = DAT_005891c0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0035ae60();
    return DAT_005891c0[0];
}
