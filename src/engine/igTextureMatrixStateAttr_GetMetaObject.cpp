/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void FUN_001316a0(void);
extern igMetaObject *g_igTextureMatrixStateAttr_metaObject[4];
igMetaObject *igTextureMatrixStateAttr_GetMetaObject(void);
}

igMetaObject *igTextureMatrixStateAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureMatrixStateAttr_metaObject[0] != 0) {
        ready = (g_igTextureMatrixStateAttr_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_001316a0();
done:
    return g_igTextureMatrixStateAttr_metaObject[0];
}
