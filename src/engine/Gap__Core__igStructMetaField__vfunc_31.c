/* 0x0030d8f0
 * Construct the value of a struct field: when the field carries a C++ constructor
 * (_cppConstructor), run it on the member at `instance + _offset`; otherwise fall back
 * to the generic igMetaField_ConstructValue. */
#include "dw4/reflected.h"
int igMetaField_ConstructValue();

void Gap__Core__igStructMetaField__vfunc_31(igStructMetaField *self, int instance) {
    int (*constructor)(int);

    constructor = (int (*)(int))(self->_cppConstructor);
    if (constructor != 0) {
        constructor(instance + self->_offset);
        return;
    }
    igMetaField_ConstructValue();
}
