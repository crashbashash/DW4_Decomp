#include "dw4/reflected.h"
extern "C" {
void FUN_0014f6d0(void);
extern igMetaObject *g_igExternalImageEntry_metaObject[4];
igMetaObject *FUN_0014f420(void);
}

igMetaObject *FUN_0014f420(void)
{
    unsigned char ready;
    if (g_igExternalImageEntry_metaObject[0] != 0) {
        ready = (g_igExternalImageEntry_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_0014f6d0();
done:
    return g_igExternalImageEntry_metaObject[0];
}
