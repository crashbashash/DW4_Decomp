/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void FUN_002c59e0(void);
extern igMetaObject *g_igEventTracker_metaObject[4];
igMetaObject *igEventTracker_GetMetaObject(void);
}

igMetaObject *igEventTracker_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igEventTracker_metaObject[0] != 0) {
        ready = (g_igEventTracker_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_002c59e0();
done:
    return g_igEventTracker_metaObject[0];
}
