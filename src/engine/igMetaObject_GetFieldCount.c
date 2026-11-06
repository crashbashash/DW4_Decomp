/* Number of meta fields a class declares. Read from the field list's `_capacity` slot (+12), not
 * `_count` (+8). Callers are the per-class InitFields functions, which pass the result to
 * igMetaObject_NameFields. */
#include "dw4/reflected.h"
int igMetaObject_GetFieldCount(igMetaObject *self) {
    return ((igMetaFieldList *)self->_metaFields)->_capacity;
}
