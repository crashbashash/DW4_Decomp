/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void igAliasMemoryPool_EnsureRegistered(void);
extern igMetaObject *g_igAliasMemoryPool_metaObject[4];
igMetaObject *igAliasMemoryPool_GetMetaObject(void);
}

igMetaObject *igAliasMemoryPool_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igAliasMemoryPool_metaObject[0] != 0) {
        ready = (g_igAliasMemoryPool_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igAliasMemoryPool_EnsureRegistered();
done:
    return g_igAliasMemoryPool_metaObject[0];
}
