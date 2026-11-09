#include "dw4/reflected.h"
extern "C" {
void FUN_00146560(void);
extern igMetaObject *g_igDefaultInterfaceManager_metaObject[4];
igMetaObject *FUN_00146470(void);
}

igMetaObject *FUN_00146470(void)
{
    unsigned char ready;
    if (g_igDefaultInterfaceManager_metaObject[0] != 0) {
        ready = (g_igDefaultInterfaceManager_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00146560();
done:
    return g_igDefaultInterfaceManager_metaObject[0];
}
