/* 0x00181000
 * Class-handle getter: returns the cached metaobject pointer held in the global
 * at 0x55fe70 (the class's own metaobject; `handle` of igCustomStateCollection in data/reflection.json).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder. */
extern int g_igCustomStateCollection_metaObject_0055fe70[4];
int Gap__Core__igCustomStateCollection__vfunc_22(void) {
    return g_igCustomStateCollection_metaObject_0055fe70[0];
}
