#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2ControllerManager_metaObject[4];
extern "C" {
void FUN_00146ee0(void);
igMetaObject *igPsx2ControllerManager_GetMetaObject(void);
}
igMetaObject *igPsx2ControllerManager_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ControllerManager_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00146ee0();
    return g_igPsx2ControllerManager_metaObject[0];
}
