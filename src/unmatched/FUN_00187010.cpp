#include "dw4/reflected.h"

extern "C" {
extern igMetaObject *g_igVec4ucMetaField_metaObject;
void FUN_001870f0(void);
igMetaObject *FUN_00187010(void);
}

igMetaObject *FUN_00187010(void)
{
    igMetaObject *meta = g_igVec4ucMetaField_metaObject;
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_001870f0();
end:
    return g_igVec4ucMetaField_metaObject;
}
