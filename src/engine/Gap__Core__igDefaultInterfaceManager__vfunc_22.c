/* 0x00149340
 * Class-handle getter: returns the cached metaobject pointer held in the global
 * at 0x55f610 (the class's own metaobject; `handle` of igDefaultInterfaceManager in data/reflection.json).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder. */
extern int g_igDefaultInterfaceManager_metaObject_0055f610[4];
int Gap__Core__igDefaultInterfaceManager__vfunc_22(void) {
    return g_igDefaultInterfaceManager_metaObject_0055f610[0];
}
