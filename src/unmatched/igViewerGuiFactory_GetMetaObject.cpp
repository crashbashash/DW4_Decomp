#include "dw4/reflected.h"
extern igMetaObject *DAT_0058cb28[4];
extern "C" {
void FUN_0045bc10(void);
igMetaObject *igViewerGuiFactory_GetMetaObject(void);
}
igMetaObject *igViewerGuiFactory_GetMetaObject(void)
{
    igMetaObject *g = DAT_0058cb28[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0045bc10();
    return DAT_0058cb28[0];
}
