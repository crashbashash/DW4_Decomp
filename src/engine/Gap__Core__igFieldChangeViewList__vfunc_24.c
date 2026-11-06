/* 0x00458370
 * Class-handle getter: vtable slot 24 of Gap::Core::igFieldChangeViewList returns the cached metaobject
 * pointer of the element class igFieldChangeView (global at 0x58c550), the slot the class
 * registration fills (see igFieldChangeViewList_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igFieldChangeView_metaObject[4];
int Gap__Core__igFieldChangeViewList__vfunc_24(void) {
    return g_igFieldChangeView_metaObject[0];
}
