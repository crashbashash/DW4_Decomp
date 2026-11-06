/* 0x00331380
 * Class-handle getter: vtable slot 22 of Gap::Core::igExternalIndexedEntry returns the cached metaobject
 * pointer in the global at 0x586418,
 * the slot the class registration fills (see igExternalIndexedEntry_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igExternalIndexedEntry_metaObject[4];
int Gap__Core__igExternalIndexedEntry__vfunc_22(void) {
    return g_igExternalIndexedEntry_metaObject[0];
}
