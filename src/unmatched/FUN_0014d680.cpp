#include "dw4/reflected.h"

extern "C" {
extern igMetaObject *g_igLineWidthExt_metaObject;
void FUN_0014d6d0(void);
igMetaObject *FUN_0014d680(void);
}

igMetaObject *FUN_0014d680(void)
{
    igMetaObject *meta = g_igLineWidthExt_metaObject;
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_0014d6d0();
end:
    return g_igLineWidthExt_metaObject;
}
