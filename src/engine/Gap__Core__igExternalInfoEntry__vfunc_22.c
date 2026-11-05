/* 0x00331370
 * Class-handle getter: vtable slot 22 of Gap::Core::igExternalInfoEntry returns the cached metaobject
 * pointer in the global at 0x5863f8,
 * the slot the class registration fills (see igExternalInfoEntry_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igExternalInfoEntry_metaObject_005863f8[4];
int Gap__Core__igExternalInfoEntry__vfunc_22(void) {
    return g_igExternalInfoEntry_metaObject_005863f8[0];
}
