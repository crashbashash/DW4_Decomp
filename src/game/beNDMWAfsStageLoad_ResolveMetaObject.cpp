/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void FUN_003cac70(void);
extern igMetaObject *g_beNDMWAfsStageLoad_metaObject[4];
igMetaObject *beNDMWAfsStageLoad_ResolveMetaObject(void);
}

igMetaObject *beNDMWAfsStageLoad_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWAfsStageLoad_metaObject[0] != 0) {
        ready = (g_beNDMWAfsStageLoad_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_003cac70();
done:
    return g_beNDMWAfsStageLoad_metaObject[0];
}
