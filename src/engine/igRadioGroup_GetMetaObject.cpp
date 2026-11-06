#include "dw4/reflected.h"
extern igMetaObject *g_igRadioGroup_metaObject[4];
extern "C" {
void igRadioGroup_EnsureRegistered(void);
igMetaObject *igRadioGroup_GetMetaObject(void);
}
igMetaObject *igRadioGroup_GetMetaObject(void)
{
    igMetaObject *g = g_igRadioGroup_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igRadioGroup_EnsureRegistered();
    return g_igRadioGroup_metaObject[0];
}
