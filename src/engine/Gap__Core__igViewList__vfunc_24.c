/* Class-handle getter: returns the metaobject pointer cached in the global at 0x58c1c0 (the igView
 * handle slot, filled in by its registrar). Same accessor idiom as the other `*_metaObject_<addr>`
 * getters in this folder. */
extern int g_igView_metaObject[4];
int Gap__Core__igViewList__vfunc_24(void) {
    return g_igView_metaObject[0];
}
