/* 0x003317b0
 * Class-handle getter: returns the cached metaobject pointer held in the global
 * at 0x586598 (the metaobject of igEnumMetaField, not of igDirectoryList itself; `handle` of igEnumMetaField in data/reflection.json).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder. */
extern int g_igEnumMetaField_metaObject[4];
int Gap__Core__igDirectoryList__vfunc_50(void) {
    return g_igEnumMetaField_metaObject[0];
}
