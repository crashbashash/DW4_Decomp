/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void FUN_003c4a90(void);
extern igMetaObject *g_beNDMWLoadCtrl2Info_metaObject[4];
igMetaObject *beNDMWLoadCtrl2Info_ResolveMetaObject(void);
}

igMetaObject *beNDMWLoadCtrl2Info_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadCtrl2Info_metaObject[0] != 0) {
        ready = (g_beNDMWLoadCtrl2Info_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_003c4a90();
done:
    return g_beNDMWLoadCtrl2Info_metaObject[0];
}
