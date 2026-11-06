/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
#include "dw4/reflected.h"
extern "C" {
void FUN_001a2940(void);
extern igMetaObject *g_igCompressedAnimationSequenceQS_metaObject[4];
igMetaObject *igCompressedAnimationSequenceQS_GetMetaObject(void);
}

igMetaObject *igCompressedAnimationSequenceQS_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igCompressedAnimationSequenceQS_metaObject[0] != 0) {
        ready = (g_igCompressedAnimationSequenceQS_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_001a2940();
done:
    return g_igCompressedAnimationSequenceQS_metaObject[0];
}
