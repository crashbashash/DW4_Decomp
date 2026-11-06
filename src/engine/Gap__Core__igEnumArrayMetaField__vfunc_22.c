/* 0x003313b0
 * Class-handle getter: vtable slot 22 of Gap::Core::igEnumArrayMetaField returns the cached metaobject
 * pointer in the global at 0x5865b0,
 * the slot the class registration fills (see igEnumArrayMetaField_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igEnumArrayMetaField_metaObject[4];
int Gap__Core__igEnumArrayMetaField__vfunc_22(void) {
    return g_igEnumArrayMetaField_metaObject[0];
}
