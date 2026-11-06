/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void FUN_0019b800(void);
extern igMetaObject *g_igProjectiveShadowShader_metaObject[4];
igMetaObject *igProjectiveShadowShader_GetMetaObject(void);
}

igMetaObject *igProjectiveShadowShader_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igProjectiveShadowShader_metaObject[0] != 0) {
        ready = (g_igProjectiveShadowShader_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_0019b800();
done:
    return g_igProjectiveShadowShader_metaObject[0];
}
