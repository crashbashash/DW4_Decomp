#include "dw4/reflected.h"
extern igMetaObject *DAT_00589e98[4];
extern "C" {
void FUN_0036c4d0(void);
igMetaObject *FUN_0036c330(void);
}
igMetaObject *FUN_0036c330(void)
{
    igMetaObject *g = DAT_00589e98[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0036c4d0();
    return DAT_00589e98[0];
}
