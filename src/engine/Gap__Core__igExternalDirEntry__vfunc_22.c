/* 0x00331390
 * Class-handle getter: vtable slot 22 of Gap::Core::igExternalDirEntry returns the cached metaobject
 * pointer in the global at 0x586450,
 * the slot the class registration fills (see igExternalDirEntry_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igExternalDirEntry_metaObject_00586450[4];
int Gap__Core__igExternalDirEntry__vfunc_22(void) {
    return g_igExternalDirEntry_metaObject_00586450[0];
}
