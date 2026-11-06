/* Checked-cast helper shared by the field-copy accessors. `FUN_00300cd0(obj, meta)` is the runtime
 * "is this object of that meta type" test (igObject::isOfType); the helper returns the object when
 * the test passes and null otherwise. It must stay an inlined static helper in a header: the
 * retail code has the test expanded inline (a `b` over the null arm). */
#ifndef DW4_TYPECAST_H
#define DW4_TYPECAST_H
#ifdef __cplusplus
extern "C" int FUN_00300cd0(...);
#else
int FUN_00300cd0();
#endif
static inline char *dw4_cast_or_null(char *x, int *meta) {
    if (x != 0 && FUN_00300cd0(x, meta[0]) != 0) {
        return x;
    }
    return 0;
}
#endif
