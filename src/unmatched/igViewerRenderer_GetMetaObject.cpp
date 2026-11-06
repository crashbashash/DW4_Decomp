#include "dw4/reflected.h"
extern "C" {
void FUN_0045b0d0(void);
extern igMetaObject *g_igViewerRenderer_metaObject[4];
igMetaObject *igViewerRenderer_GetMetaObject(void);
}

igMetaObject *igViewerRenderer_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igViewerRenderer_metaObject[0] != 0) {
        ready = (g_igViewerRenderer_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_0045b0d0();
done:
    return g_igViewerRenderer_metaObject[0];
}
