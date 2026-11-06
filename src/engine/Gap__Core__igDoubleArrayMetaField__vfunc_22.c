/* 0x00331400
 * Class-handle getter: returns the cached metaobject pointer held in the global
 * at 0x586648 (the class's own metaobject; `handle` of igDoubleArrayMetaField in data/reflection.json).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder. */
extern int g_igDoubleArrayMetaField_metaObject[4];
int Gap__Core__igDoubleArrayMetaField__vfunc_22(void) {
    return g_igDoubleArrayMetaField_metaObject[0];
}
