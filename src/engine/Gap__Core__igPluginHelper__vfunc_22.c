/* 0x003311c0
 * Class-handle getter: vtable slot 22 of Gap::Core::igPluginHelper returns the cached metaobject
 * pointer in the global at 0x585ab8, the slot the class registration fills (see igPluginHelper_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igPluginHelper_metaObject_00585ab8[4];
int Gap__Core__igPluginHelper__vfunc_22(void) {
    return g_igPluginHelper_metaObject_00585ab8[0];
}
