#include "dw4/reflected.h"
extern igMetaObject *g_igRadioGroupModel_metaObject[4];
extern "C" {
void igRadioGroupModel_RunStaticInit(void);
igMetaObject *igRadioGroupModel_GetMetaObject(void);
}
igMetaObject *igRadioGroupModel_GetMetaObject(void)
{
    igMetaObject *g = g_igRadioGroupModel_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igRadioGroupModel_RunStaticInit();
    return g_igRadioGroupModel_metaObject[0];
}
