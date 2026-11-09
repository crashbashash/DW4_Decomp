#include "dw4/reflected.h"

extern "C" {
extern igMetaObject *g_igDecalExt_metaObject;
void FUN_0014f920(void);
igMetaObject *FUN_0014f8d0(void);
}

igMetaObject *FUN_0014f8d0(void)
{
    igMetaObject *meta = g_igDecalExt_metaObject;
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_0014f920();
end:
    return g_igDecalExt_metaObject;
}
