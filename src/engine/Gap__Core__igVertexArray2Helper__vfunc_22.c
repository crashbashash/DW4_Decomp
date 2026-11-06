/* 0x00180e30
 * Class-handle getter: returns the metaobject pointer cached in the global at
 * 0x55f9d0 (the igVertexArray2Helper handle slot, filled in by its registrar; see
 * docs/engine/reflection-metadata.md).  Same accessor idiom as the other
 * `*_metaObject_<addr>` getters in this folder. */
extern int g_igVertexArray2Helper_metaObject[4];
int Gap__Core__igVertexArray2Helper__vfunc_22(void) {
    return g_igVertexArray2Helper_metaObject[0];
}
