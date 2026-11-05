/* 0x00142260
 * Class-handle getter: returns the metaobject pointer cached in the global at
 * 0x55ebc0 (the igVisualContextAttrDefaultManager handle slot, filled in by its registrar; see
 * docs/engine/reflection-metadata.md).  Same accessor idiom as the other
 * `*_metaObject_<addr>` getters in this folder. */
extern int g_igVisualContextAttrDefaultManager_metaObject_0055ebc0[4];
int Gap__Core__igVisualContextAttrDefaultManager__vfunc_22(void) {
    return g_igVisualContextAttrDefaultManager_metaObject_0055ebc0[0];
}
