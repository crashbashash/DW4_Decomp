/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void FUN_00131240(void);
extern igMetaObject *g_igTextureUnloadAttr_metaObject[4];
igMetaObject *igTextureUnloadAttr_GetMetaObject(void);
}

igMetaObject *igTextureUnloadAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureUnloadAttr_metaObject[0] != 0) {
        ready = (g_igTextureUnloadAttr_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00131240();
done:
    return g_igTextureUnloadAttr_metaObject[0];
}
