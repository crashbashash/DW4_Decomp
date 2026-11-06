/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void FUN_00133290(void);
extern igMetaObject *g_igTexGenMatrixAttr_metaObject[4];
igMetaObject *igTexGenMatrixAttr_GetMetaObject(void);
}

igMetaObject *igTexGenMatrixAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTexGenMatrixAttr_metaObject[0] != 0) {
        ready = (g_igTexGenMatrixAttr_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00133290();
done:
    return g_igTexGenMatrixAttr_metaObject[0];
}
