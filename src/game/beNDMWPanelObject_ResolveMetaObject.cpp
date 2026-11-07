#include "dw4/reflected.h"
extern "C" {
void FUN_003bec70(void);
extern igMetaObject *g_beNDMWPanelObject_metaObject[4];
igMetaObject *beNDMWPanelObject_ResolveMetaObject(void);
}

igMetaObject *beNDMWPanelObject_ResolveMetaObject(void)
{
    igMetaObject *meta = g_beNDMWPanelObject_metaObject[0];
    if (!meta || ((meta->_validity & 4) != 0) == false) {
        FUN_003bec70();
    }
    return g_beNDMWPanelObject_metaObject[0];
}
