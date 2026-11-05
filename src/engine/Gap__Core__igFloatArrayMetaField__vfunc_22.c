/* 0x00331340
 * Class-handle getter: vtable slot 22 of Gap::Core::igFloatArrayMetaField returns the cached metaobject
 * pointer in the global at 0x586388,
 * the slot the class registration fills (see igFloatArrayMetaField_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igFloatArrayMetaField_metaObject_00586388[4];
int Gap__Core__igFloatArrayMetaField__vfunc_22(void) {
    return g_igFloatArrayMetaField_metaObject_00586388[0];
}
