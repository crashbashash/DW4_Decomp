/* 0x00458260
 * Class-handle getter: vtable slot 22 of Gap::Core::igFieldChangeViewList returns the cached metaobject
 * pointer in the global at 0x58c548,
 * the slot the class registration fills (see igFieldChangeViewList_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igFieldChangeViewList_metaObject[4];
int Gap__Core__igFieldChangeViewList__vfunc_22(void) {
    return g_igFieldChangeViewList_metaObject[0];
}
