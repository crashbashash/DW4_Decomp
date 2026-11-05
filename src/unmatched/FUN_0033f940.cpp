#include "dw4/reflected.h"
extern igMetaObject *DAT_00587a78[4];
extern "C" {
void FUN_0033f9d0(void);
igMetaObject *FUN_0033f940(void);
}
igMetaObject *FUN_0033f940(void)
{
    igMetaObject *g = DAT_00587a78[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0033f9d0();
    return DAT_00587a78[0];
}
