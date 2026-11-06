#include "dw4/reflected.h"
extern igMetaObject *g_igRendererOrderedList_metaObject[4];
extern "C" {
void igRendererOrderedList_EnsureRegistered(void);
igMetaObject *igRendererOrderedList_GetMetaObject(void);
}
igMetaObject *igRendererOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igRendererOrderedList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRendererOrderedList_EnsureRegistered();
    return g_igRendererOrderedList_metaObject[0];
}
