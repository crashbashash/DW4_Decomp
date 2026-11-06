#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2Folder_metaObject[4];
extern "C" {
void FUN_002d0110(void);
igMetaObject *igPsx2Folder_GetMetaObject(void);
}
igMetaObject *igPsx2Folder_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Folder_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002d0110();
    return g_igPsx2Folder_metaObject[0];
}
