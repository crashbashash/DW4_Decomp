#include "dw4/reflected.h"
int igObject_Destroy();

/* slot 40 of igLightAttr: set the _vc reference (+140). Reference-counted assignment: retain the
 * new object, release the old one (destroying it when its 23-bit count reaches zero), then store
 * the new one. */
void Gap__Core__igLightAttr__vfunc_40(igLightAttr *self, igObject *vertexCache) {
    igObject *previousVertexCache;
    if (vertexCache != 0) {
        vertexCache->_refCount = vertexCache->_refCount + 1;
    }
    previousVertexCache = (igObject *)(self->_vc);
    if (previousVertexCache != 0) {
        previousVertexCache->_refCount = previousVertexCache->_refCount - 1;
        if ((previousVertexCache->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previousVertexCache);
        }
    }
    self->_vc = (int)vertexCache;
}
