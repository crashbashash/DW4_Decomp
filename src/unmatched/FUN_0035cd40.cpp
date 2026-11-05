#include "dw4/reflected.h"
extern igMetaObject *DAT_005892b0[4];
extern "C" {
void FUN_0035ce60(void);
igMetaObject *FUN_0035cd40(void);
}
igMetaObject *FUN_0035cd40(void)
{
    igMetaObject *g = DAT_005892b0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0035ce60();
    return DAT_005892b0[0];
}
