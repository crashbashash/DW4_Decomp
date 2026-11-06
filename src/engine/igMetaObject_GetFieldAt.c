/* The meta field at `index` in the class's `_metaFields` list. Its callers (the *_InitFields
 * functions) patch the returned field's settings. The item array is read at +8 of the list object,
 * as in the retail load sequence. */
#include "dw4/reflected.h"
int igMetaObject_GetFieldAt(igMetaObject *self, int index) {
    return *(int *)(*(int *)((char *)(self->_metaFields) + 8) + (index * 4));
}
