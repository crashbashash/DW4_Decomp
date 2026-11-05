#include "dw4/reflected.h"
extern igMetaObject *DAT_00589638[4];
extern "C" {
void FUN_00361440(void);
igMetaObject *FUN_003613b0(void);
}
igMetaObject *FUN_003613b0(void)
{
    igMetaObject *g = DAT_00589638[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00361440();
    return DAT_00589638[0];
}
