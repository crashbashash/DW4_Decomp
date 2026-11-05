#include "dw4/reflected.h"
extern igMetaObject *DAT_00587fc8[4];
extern "C" {
void FUN_00346200(void);
igMetaObject *FUN_00346170(void);
}
igMetaObject *FUN_00346170(void)
{
    igMetaObject *g = DAT_00587fc8[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00346200();
    return DAT_00587fc8[0];
}
