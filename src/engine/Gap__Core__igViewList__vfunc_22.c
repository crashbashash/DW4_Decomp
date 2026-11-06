/* 0x00458320
 * Class-handle getter: returns the metaobject pointer cached in the global at
 * 0x58c1b8 (the igViewList handle slot, filled in by its registrar; see
 * docs/engine/reflection-metadata.md).  Same accessor idiom as the other
 * `*_metaObject_<addr>` getters in this folder. */
extern int g_igViewList_metaObject[4];
int Gap__Core__igViewList__vfunc_22(void) {
    return g_igViewList_metaObject[0];
}
