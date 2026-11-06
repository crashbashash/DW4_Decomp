/* The object-reference field's raw-field-memory read (vtable +0xcc, slot 51): run the
 * igRefMetaField base read, then take a reference on the object now held in *valueSlot when the
 * field is reference counted (_refCounted, +60) or destructed (_destruct, +53). */
#include "dw4/reflected.h"
int igRefMetaField_ReadRawFieldMem();

void Gap__Core__igObjectRefMetaField__vfunc_51(igObjectRefMetaField *self, igObject **valueSlot) {
    igObject *object;

    igRefMetaField_ReadRawFieldMem();
    if ((self->_refCounted != 0) || (self->_destruct != 0)) {
        object = *valueSlot;
        if (object != 0) {
            object->_refCount = object->_refCount + 1;
        }
    }
}
