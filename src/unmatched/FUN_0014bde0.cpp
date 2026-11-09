#include "dw4/reflected.h"
extern "C" {
void FUN_0014be70(void);
extern igMetaObject *g_igPrimLengthArray1_1_metaObject[4];
igMetaObject *FUN_0014bde0(void);
}

igMetaObject *FUN_0014bde0(void)
{
    unsigned char ready;
    if (g_igPrimLengthArray1_1_metaObject[0] != 0) {
        ready = (g_igPrimLengthArray1_1_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_0014be70();
done:
    return g_igPrimLengthArray1_1_metaObject[0];
}
