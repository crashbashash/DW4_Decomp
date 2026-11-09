#include "dw4/reflected.h"

extern "C" {
extern igMetaObject *g_igVectorMorphing_metaObject;
void FUN_00186e40(void);
igMetaObject *FUN_00186db0(void);
}

igMetaObject *FUN_00186db0(void)
{
    igMetaObject *meta = g_igVectorMorphing_metaObject;
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_00186e40();
end:
    return g_igVectorMorphing_metaObject;
}
