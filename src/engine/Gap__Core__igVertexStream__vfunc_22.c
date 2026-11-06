/* 0x00180ea0
 * Class-handle getter: returns the metaobject pointer cached in the global at
 * 0x55fa10 (the igVertexStream handle slot, filled in by its registrar; see
 * docs/engine/reflection-metadata.md).  Same accessor idiom as the other
 * `*_metaObject_<addr>` getters in this folder. */
extern int g_igVertexStream_metaObject[4];
int Gap__Core__igVertexStream__vfunc_22(void) {
    return g_igVertexStream_metaObject[0];
}
