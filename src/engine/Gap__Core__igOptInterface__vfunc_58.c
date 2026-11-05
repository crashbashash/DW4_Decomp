/* 0x0022ca10
 * Class-handle getter: vtable slot 58 of Gap::Core::igOptInterface returns the metaobject slot of
 * igOptBase (global at 0x56d890), not of igOptInterface itself (see igOptBase_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igOptBase_metaObject_0056d890[4];
int Gap__Core__igOptInterface__vfunc_58(void) {
    return g_igOptBase_metaObject_0056d890[0];
}
