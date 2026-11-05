/* 0x003318e0
 * Class-handle getter: vtable slot 22 of Gap::Core::igObjectStringMap returns the cached metaobject
 * pointer in the global at 0x585b08, the slot the class registration fills (see igObjectStringMap_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igObjectStringMap_metaObject_00585b08[4];
int Gap__Core__igObjectStringMap__vfunc_22(void) {
    return g_igObjectStringMap_metaObject_00585b08[0];
}
