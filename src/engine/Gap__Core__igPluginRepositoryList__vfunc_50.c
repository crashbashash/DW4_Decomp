/* 0x00331910
 * Class-handle getter: vtable slot 50 of Gap::Core::igPluginRepositoryList returns the metaobject slot of
 * igRawRefMetaField (global at 0x585a80), not of igPluginRepositoryList itself.
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igRawRefMetaField_metaObject[4];
int Gap__Core__igPluginRepositoryList__vfunc_50(void) {
    return g_igRawRefMetaField_metaObject[0];
}
