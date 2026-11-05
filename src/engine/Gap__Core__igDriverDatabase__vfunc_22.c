/* 0x003313d0
 * Class-handle getter: returns the cached metaobject pointer held in the global
 * at 0x5865d0 (the class's own metaobject; `handle` of igDriverDatabase in data/reflection.json).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder. */
extern int g_igDriverDatabase_metaObject_005865d0[4];
int Gap__Core__igDriverDatabase__vfunc_22(void) {
    return g_igDriverDatabase_metaObject_005865d0[0];
}
