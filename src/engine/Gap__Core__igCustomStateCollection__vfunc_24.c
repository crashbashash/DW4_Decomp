/* 0x001810f0
 * Class-handle getter: returns the cached metaobject pointer held in the global
 * at 0x55fe88 (the metaobject of igCustomState, not of igCustomStateCollection itself; `handle` of igCustomState in data/reflection.json).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder. */
extern int g_igCustomState_metaObject[4];
int Gap__Core__igCustomStateCollection__vfunc_24(void) {
    return g_igCustomState_metaObject[0];
}
