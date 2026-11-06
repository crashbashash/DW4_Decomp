/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void igStringMetaField_EnsureRegistered(void);
extern igMetaObject *g_igStringMetaField_metaObject[4];
igMetaObject *igStringMetaField_GetMetaObject(void);
}

igMetaObject *igStringMetaField_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igStringMetaField_metaObject[0] != 0) {
        ready = (g_igStringMetaField_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igStringMetaField_EnsureRegistered();
done:
    return g_igStringMetaField_metaObject[0];
}
