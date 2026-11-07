#include "dw4/reflected.h"
extern igMetaObject *DAT_005622b8[4];
extern "C" {
void FUN_001a8800(void);
igMetaObject *FUN_001a8520(void);
}
igMetaObject *FUN_001a8520(void)
{
    igMetaObject *g = DAT_005622b8[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a8800();
    return DAT_005622b8[0];
}
