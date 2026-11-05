/* 0x00331420
 * Class-handle getter: returns the cached metaobject pointer held in the global
 * at 0x586668 (the class's own metaobject; `handle` of igDirectory in data/reflection.json).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder. */
extern int g_igDirectory_metaObject_00586668[4];
int Gap__Core__igDirectory__vfunc_22(void) {
    return g_igDirectory_metaObject_00586668[0];
}
