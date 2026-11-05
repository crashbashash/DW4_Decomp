#include "dw4/reflected.h"
extern igMetaObject *DAT_00589938[4];
extern "C" {
void FUN_00365f10(void);
igMetaObject *FUN_00365dc0(void);
}
igMetaObject *FUN_00365dc0(void)
{
    igMetaObject *g = DAT_00589938[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00365f10();
    return DAT_00589938[0];
}
