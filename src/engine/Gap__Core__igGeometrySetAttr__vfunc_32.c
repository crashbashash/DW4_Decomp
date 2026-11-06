/* Setter for the retained _vc reference. Takes a reference on the new object, drops the old one
 * (destroying it when its low 23 reference bits reach zero), then stores. */
#include "dw4/reflected.h"
int igObject_Destroy();

void Gap__Core__igGeometrySetAttr__vfunc_32(igGeometrySetAttr *self, igObject *newVc) {
    igObject *oldVc;
    if (newVc != 0) {
        newVc->_refCount = newVc->_refCount + 1;
    }
    oldVc = (igObject *)self->_vc;
    if (oldVc != 0) {
        oldVc->_refCount = oldVc->_refCount - 1;
        if ((oldVc->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(oldVc);
        }
    }
    self->_vc = (int)newVc;
}
