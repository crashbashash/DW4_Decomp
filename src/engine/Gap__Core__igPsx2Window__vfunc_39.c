/* 0x00148be0 — igPsx2Window setter for the _vc field (the view context
 * reference, +0x18).  Standard reference-counted assignment: retain the new
 * object, release the old one (destroying it when its count reaches zero),
 * then store.  Returns 0 and leaves the field alone when handed NULL, 1 once
 * the new view context is stored.  The refcount is the low 23 bits of
 * igObject::_refCount (see src/engine/ref-field-lifecycle.cpp). */
#include "dw4/reflected.h"
void igObject_Destroy(void *);

int Gap__Core__igPsx2Window__vfunc_39(igPsx2Window *self, igObject *viewContext) {
    igObject *previous;
    if (viewContext != 0) {
        /* retail repeats the NULL test around the retain; dropping it changes the bytes */
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
