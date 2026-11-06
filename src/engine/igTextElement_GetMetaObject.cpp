#include "dw4/reflected.h"
extern igMetaObject *g_igTextElement_metaObject[4];
extern "C" {
void igTextElement_EnsureRegistered(void);
igMetaObject *igTextElement_GetMetaObject(void);
}
igMetaObject *igTextElement_GetMetaObject(void)
{
    igMetaObject *g = g_igTextElement_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igTextElement_EnsureRegistered();
    return g_igTextElement_metaObject[0];
}
