/* 0x0030d970
 * SetToDefault for a struct field: when the field carries a C++ constructor
 * (_cppConstructor), reset the value in place by running the destructor
 * (_cppDestructor) and then the constructor on the member at
 * `instance + _offset`.  A field without one falls back to the generic
 * igMetaField_SetToDefault (the base +0x70 body). */
#include "dw4/reflected.h"
int igMetaField_SetToDefault();

void Gap__Core__igStructMetaField__vfunc_28(igStructMetaField *self, int instance) {
    if (self->_cppConstructor != 0) {
        ((int (*)())self->_cppDestructor)(instance + self->_offset);
        ((int (*)())self->_cppConstructor)(instance + self->_offset);
        return;
    }
    igMetaField_SetToDefault();
}
