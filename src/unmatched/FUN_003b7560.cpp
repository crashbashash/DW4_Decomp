#include "dw4/reflected.h"
extern igMetaObject *DAT_0058ad28[4];
extern "C" {
void FUN_003b7630(void);
igMetaObject *FUN_003b7560(void);
}
igMetaObject *FUN_003b7560(void)
{
    igMetaObject *g = DAT_0058ad28[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003b7630();
    return DAT_0058ad28[0];
}
