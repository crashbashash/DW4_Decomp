/* Checked-cast helper shared by the field-copy accessors. `igObject_IsKindOf(obj, meta)` is the runtime
 * "is this object of that meta type" test (igObject::isOfType); the helper returns the object when
 * the test passes and null otherwise. It must stay an inlined static helper in a header: the
 * retail code has the test expanded inline (a `b` over the null arm). */
#ifndef DW4_TYPECAST_H
#define DW4_TYPECAST_H
#include "dw4/core/igObject.h"
static inline char *dw4_cast_or_null(char *x, int *meta) {
    if (x != 0 && igObject_IsKindOf((struct igObject *)x, (struct igMetaObject *)meta[0]) != 0) {
        return x;
    }
    return 0;
}
#ifdef __cplusplus
/* The same test against a metaobject variable, read inside the test as the retail code does. */
static inline char *dw4_cast_or_null(char *x, struct igMetaObject **meta) {
    if (x != 0 && igObject_IsKindOf((struct igObject *)x, *meta) != 0) {
        return x;
    }
    return 0;
}
#endif
#endif
