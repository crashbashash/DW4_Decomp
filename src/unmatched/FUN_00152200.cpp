#include "dw4/reflected.h"
extern "C" {
void FUN_001522c0(void);
extern igMetaObject *g_igPsx2VertexArray2_metaObject[4];
igMetaObject *FUN_00152200(void);
}

igMetaObject *FUN_00152200(void)
{
    unsigned char ready;
    if (g_igPsx2VertexArray2_metaObject[0] != 0) {
        ready = (g_igPsx2VertexArray2_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_001522c0();
done:
    return g_igPsx2VertexArray2_metaObject[0];
}
