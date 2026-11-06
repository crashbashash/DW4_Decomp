/* 0x003317d0
 * Class-handle getter: vtable slot 22 of Gap::Core::igErrorHandler returns the cached metaobject
 * pointer in the global at 0x586590,
 * the slot the class registration fills (see igErrorHandler_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igErrorHandler_metaObject[4];
int Gap__Core__igErrorHandler__vfunc_22(void) {
    return g_igErrorHandler_metaObject[0];
}
