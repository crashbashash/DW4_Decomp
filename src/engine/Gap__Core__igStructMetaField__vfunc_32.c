/* 0x0030d930
 * Destruct the value of a struct field: when the field carries a C++ destructor
 * (_cppDestructor), run it on the member at `instance + _offset`; otherwise fall back
 * to the generic igMetaField_DestructValue. */
#include "dw4/reflected.h"
int igMetaField_DestructValue();

void Gap__Core__igStructMetaField__vfunc_32(igStructMetaField *self, int instance) {
    int (*destructor)(int);

    destructor = (int (*)(int))(self->_cppDestructor);
    if (destructor != 0) {
        destructor(instance + self->_offset);
        return;
    }
    igMetaField_DestructValue();
}
