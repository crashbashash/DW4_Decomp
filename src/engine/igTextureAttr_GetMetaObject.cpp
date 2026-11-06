/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void FUN_00132cf0(void);
extern igMetaObject *g_igTextureAttr_metaObject[4];
igMetaObject *igTextureAttr_GetMetaObject(void);
}

igMetaObject *igTextureAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureAttr_metaObject[0] != 0) {
        ready = (g_igTextureAttr_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00132cf0();
done:
    return g_igTextureAttr_metaObject[0];
}
