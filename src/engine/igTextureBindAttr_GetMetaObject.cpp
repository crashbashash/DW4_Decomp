/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void FUN_00132a00(void);
extern igMetaObject *g_igTextureBindAttr_metaObject[4];
igMetaObject *igTextureBindAttr_GetMetaObject(void);
}

igMetaObject *igTextureBindAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureBindAttr_metaObject[0] != 0) {
        ready = (g_igTextureBindAttr_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00132a00();
done:
    return g_igTextureBindAttr_metaObject[0];
}
