#include "dw4/reflected.h"
extern igMetaObject *g_igProgramFile_metaObject[4];
extern "C" {
void FUN_002cea80(void);
igMetaObject *igProgramFile_GetMetaObject(void);
}
igMetaObject *igProgramFile_GetMetaObject(void)
{
    igMetaObject *g = g_igProgramFile_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002cea80();
    return g_igProgramFile_metaObject[0];
}
