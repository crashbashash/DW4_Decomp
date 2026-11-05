#include "dw4/reflected.h"
extern igMetaObject *DAT_0058b050[4];
extern "C" {
void FUN_003bbc90(void);
igMetaObject *FUN_003bbbd0(void);
}
igMetaObject *FUN_003bbbd0(void)
{
    igMetaObject *g = DAT_0058b050[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003bbc90();
    return DAT_0058b050[0];
}
