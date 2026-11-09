#include "dw4/reflected.h"

extern "C" {
extern igMetaObject *g_igPsx2Window_metaObject;
void FUN_00146b80(void);
igMetaObject *FUN_00146a60(void);
}

igMetaObject *FUN_00146a60(void)
{
    igMetaObject *meta = g_igPsx2Window_metaObject;
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_00146b80();
end:
    return g_igPsx2Window_metaObject;
}
