/* 0x00303980
 * Reset the object this field refers to. `instance` is the object that owns the
 * field; the slot at this field's `_offset` holds an igObject pointer, and a
 * non-null one gets igObject_ResetFields. */
#include "dw4/reflected.h"
int igObject_ResetFields(int);

void Gap__Core__igObjectRefMetaField__vfunc_39(igObjectRefMetaField *self, int instance) {
    int object;

    object = *(int *)(instance + self->_offset);
    if (object != 0) {
        igObject_ResetFields(object);
    }
}
