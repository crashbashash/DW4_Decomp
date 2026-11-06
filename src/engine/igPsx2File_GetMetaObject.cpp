#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2File_metaObject[4];
extern "C" {
void FUN_002d02b0(void);
igMetaObject *igPsx2File_GetMetaObject(void);
}
igMetaObject *igPsx2File_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2File_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002d02b0();
    return g_igPsx2File_metaObject[0];
}
