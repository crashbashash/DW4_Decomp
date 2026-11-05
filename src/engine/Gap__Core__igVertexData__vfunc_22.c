/* 0x00181080
 * Class-handle getter: returns the metaobject pointer cached in the global at
 * 0x55fa58 (the igVertexData handle slot, filled in by its registrar; see
 * docs/engine/reflection-metadata.md).  Same accessor idiom as the other
 * `*_metaObject_<addr>` getters in this folder. */
extern int g_igVertexData_metaObject_0055fa58[4];
int Gap__Core__igVertexData__vfunc_22(void) {
    return g_igVertexData_metaObject_0055fa58[0];
}
