/* 0x00193d60
 * Class-handle getter: returns the metaobject pointer cached in the global at
 * 0x560f70 (the igVec3fMetaField handle slot, filled in by its registrar; see
 * docs/engine/reflection-metadata.md).  Same accessor idiom as the other
 * `*_metaObject_<addr>` getters in this folder. */
extern int g_igVec3fMetaField_metaObject[4];
int Gap__Core__igVec3fMetaField__vfunc_22(void) {
    return g_igVec3fMetaField_metaObject[0];
}
