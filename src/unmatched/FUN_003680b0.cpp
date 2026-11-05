#include "dw4/reflected.h"
extern igMetaObject *DAT_00589b58[4];
extern "C" {
void FUN_003681a0(void);
igMetaObject *FUN_003680b0(void);
}
igMetaObject *FUN_003680b0(void)
{
    igMetaObject *g = DAT_00589b58[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003681a0();
    return DAT_00589b58[0];
}
