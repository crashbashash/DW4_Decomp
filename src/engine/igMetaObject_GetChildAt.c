/* The child meta object at `index` in the class's `_children` list. Same list layout as
 * igMetaObject_GetFieldAt: the item array is read at +8 of the list object, as in the retail load
 * sequence. */
#include "dw4/reflected.h"
int igMetaObject_GetChildAt(igMetaObject *self, int index) {
    return *(int *)(*(int *)((char *)(self->_children) + 8) + (index * 4));
}
