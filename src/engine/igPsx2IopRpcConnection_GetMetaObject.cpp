#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2IopRpcConnection_metaObject[4];
extern "C" {
void FUN_002cff30(void);
igMetaObject *igPsx2IopRpcConnection_GetMetaObject(void);
}
igMetaObject *igPsx2IopRpcConnection_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2IopRpcConnection_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002cff30();
    return g_igPsx2IopRpcConnection_metaObject[0];
}
