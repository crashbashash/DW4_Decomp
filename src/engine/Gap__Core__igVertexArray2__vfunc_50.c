/* 0x00180ee0
 * Class-handle getter: returns the metaobject pointer cached in the global at
 * 0x55fa90 (the igVertexArray1_1 handle slot, filled in by its registrar; see
 * docs/engine/reflection-metadata.md).  Same accessor idiom as the other
 * `*_metaObject_<addr>` getters in this folder. */
extern int g_igVertexArray1_1_metaObject_0055fa90[4];
int Gap__Core__igVertexArray2__vfunc_50(void) {
    return g_igVertexArray1_1_metaObject_0055fa90[0];
}
