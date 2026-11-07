#include "dw4/reflected.h"
extern igMetaObject *DAT_00561b48[4];
extern "C" {
void FUN_001a1990(void);
igMetaObject *FUN_001a18b0(void);
}
igMetaObject *FUN_001a18b0(void)
{
    igMetaObject *g = DAT_00561b48[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a1990();
    return DAT_00561b48[0];
}
