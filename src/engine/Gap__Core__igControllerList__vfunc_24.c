/* 0x00149390
 * Class-handle getter: returns the cached metaobject pointer held in the global
 * at 0x55f6b0 (the metaobject of igController, not of igControllerList itself; `handle` of igController in data/reflection.json).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder. */
extern int g_igController_metaObject_0055f6b0[4];
int Gap__Core__igControllerList__vfunc_24(void) {
    return g_igController_metaObject_0055f6b0[0];
}
