/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void FUN_001e4620(void);
extern igMetaObject *g_igMersenneTwisterRandomNumber_metaObject[4];
igMetaObject *igMersenneTwisterRandomNumber_GetMetaObject(void);
}

igMetaObject *igMersenneTwisterRandomNumber_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igMersenneTwisterRandomNumber_metaObject[0] != 0) {
        ready = (g_igMersenneTwisterRandomNumber_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_001e4620();
done:
    return g_igMersenneTwisterRandomNumber_metaObject[0];
}
