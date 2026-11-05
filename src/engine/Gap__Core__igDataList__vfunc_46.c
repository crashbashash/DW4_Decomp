/* 0x002d6380
 * Class-handle getter: returns the cached metaobject pointer held in the global
 * at 0x5868f8 (the metaobject of igContext, not of igDataList itself; `handle` of igContext in data/reflection.json).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder. */
extern int g_igContext_metaObject_005868f8[4];
int Gap__Core__igDataList__vfunc_46(void) {
    return g_igContext_metaObject_005868f8[0];
}
