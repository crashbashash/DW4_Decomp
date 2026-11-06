/* Setter for the _vc field (the view context reference, +0x18). Retains the new object, releases
 * the old one (destroying it when its count reaches zero), then stores. Returns 0 and leaves the
 * field alone when handed NULL, 1 once the new view context is stored. The refcount is the low 23
 * bits of igObject::_refCount. */
#include "dw4/reflected.h"
void igObject_Destroy(void *);

int Gap__igPsx2Window__vfunc_39(igPsx2Window *self, igObject *viewContext) {
    igObject *previous;
    if (viewContext != 0) {
        /* The NULL test is repeated around the retain; dropping it changes the bytes. */
        if (viewContext != 0) {
            viewContext->_refCount = viewContext->_refCount + 1;
        }
        previous = (igObject *)(self->_vc);
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(previous);
            }
        }
        self->_vc = (int)(viewContext);
        return 1;
    }
    return 0;
}
