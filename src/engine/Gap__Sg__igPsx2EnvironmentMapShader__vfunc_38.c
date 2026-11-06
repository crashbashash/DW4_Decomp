/* igPsx2EnvironmentMapShader setter for _diffuseTextureBind (+0x24). Reference-counted assignment:
 * retain the new object, release the previous one (destroying it when its count reaches zero),
 * store, then clear _configured so the shader is set up again before it is next used. The refcount
 * is the low 23 bits of igObject::_refCount. */
#include "dw4/reflected.h"
void igObject_Destroy(void *);

void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_38(igPsx2EnvironmentMapShader *self, igObject *value) {
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = (igObject *)(self->_diffuseTextureBind);
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->_diffuseTextureBind = (int)(value);
    self->_configured = 0;
}
