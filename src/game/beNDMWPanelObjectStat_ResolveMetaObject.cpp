#include "dw4/reflected.h"
extern igMetaObject *DAT_0058b260[4];
extern "C" {
void FUN_003be360(void);
igMetaObject *beNDMWPanelObjectStat_ResolveMetaObject(void);
}
igMetaObject *beNDMWPanelObjectStat_ResolveMetaObject(void)
{
    igMetaObject *g = DAT_0058b260[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003be360();
    return DAT_0058b260[0];
}
