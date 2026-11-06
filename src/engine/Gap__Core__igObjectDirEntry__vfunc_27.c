/* Takes one more reference on `object` (null-safe): bumps its shared igObject _refCount. */
#include "dw4/reflected.h"
void Gap__Core__igObjectDirEntry__vfunc_27(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}
