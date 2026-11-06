/* Class-handle getter: returns the metaobject pointer cached in the global at 0x560f38 (the
 * igVec4fMetaField handle slot, filled in by its registrar). Same accessor idiom as the other
 * `*_metaObject_<addr>` getters in this folder. */
extern int g_igVec4fMetaField_metaObject[4];
int Gap__Core__igVec4fMetaField__vfunc_22(void) {
    return g_igVec4fMetaField_metaObject[0];
}
