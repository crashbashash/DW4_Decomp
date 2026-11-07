#include "dw4/reflected.h"
extern igMetaObject *DAT_005611d8[4];
extern "C" {
void FUN_00195290(void);
igMetaObject *FUN_00194ef0(void);
}
igMetaObject *FUN_00194ef0(void)
{
    igMetaObject *g = DAT_005611d8[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00195290();
    return DAT_005611d8[0];
}
