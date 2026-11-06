/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void FUN_00188520(void);
extern igMetaObject *g_igPlane_metaObject[4];
igMetaObject *igPlane_GetMetaObject(void);
}

igMetaObject *igPlane_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igPlane_metaObject[0] != 0) {
        ready = (g_igPlane_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00188520();
done:
    return g_igPlane_metaObject[0];
}
