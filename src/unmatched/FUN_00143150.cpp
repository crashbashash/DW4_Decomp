#include "dw4/reflected.h"

extern "C" {
extern igMetaObject *g_igPsx2AudioContext_metaObject;
void FUN_001433d0(void);
igMetaObject *FUN_00143150(void);
}

igMetaObject *FUN_00143150(void)
{
    igMetaObject *meta = g_igPsx2AudioContext_metaObject;
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_001433d0();
end:
    return g_igPsx2AudioContext_metaObject;
}
