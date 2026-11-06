/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void FUN_00232320(void);
extern igMetaObject *g_igMessageDefaultReceiver_metaObject[4];
igMetaObject *igMessageDefaultReceiver_GetMetaObject(void);
}

igMetaObject *igMessageDefaultReceiver_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igMessageDefaultReceiver_metaObject[0] != 0) {
        ready = (g_igMessageDefaultReceiver_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00232320();
done:
    return g_igMessageDefaultReceiver_metaObject[0];
}
