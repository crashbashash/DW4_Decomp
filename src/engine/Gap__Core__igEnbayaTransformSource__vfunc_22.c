/* 0x001e32b0
 * Class-handle getter: vtable slot 22 of Gap::Core::igEnbayaTransformSource returns the cached metaobject
 * pointer in the global at 0x561b48,
 * the slot the class registration fills (see igEnbayaTransformSource_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igEnbayaTransformSource_metaObject_00561b48[4];
int Gap__Core__igEnbayaTransformSource__vfunc_22(void) {
    return g_igEnbayaTransformSource_metaObject_00561b48[0];
}
