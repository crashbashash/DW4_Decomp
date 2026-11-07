#include "dw4/reflected.h"
extern "C" {
void FUN_002c18b0(void);
extern igMetaObject *DAT_00586028[4];
igMetaObject *FUN_002c1860(void);
}

igMetaObject *FUN_002c1860(void)
{
    unsigned char ready;
    if (DAT_00586028[0] != 0) {
        ready = (DAT_00586028[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_002c18b0();
done:
    return DAT_00586028[0];
}
