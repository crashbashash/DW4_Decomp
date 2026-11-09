#include "dw4/reflected.h"
extern "C" {
void FUN_00186f70(void);
extern igMetaObject *g_igVectorBlending_metaObject[4];
igMetaObject *FUN_00186ee0(void);
}

igMetaObject *FUN_00186ee0(void)
{
    unsigned char ready;
    if (g_igVectorBlending_metaObject[0] != 0) {
        ready = (g_igVectorBlending_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00186f70();
done:
    return g_igVectorBlending_metaObject[0];
}
