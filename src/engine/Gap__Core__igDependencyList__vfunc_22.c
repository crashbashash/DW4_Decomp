/* 0x00331790
 * Class-handle getter: returns the cached metaobject pointer held in the global
 * at 0x586768 (the class's own metaobject; `handle` of igDependencyList in data/reflection.json).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder. */
extern int g_igDependencyList_metaObject_00586768[4];
int Gap__Core__igDependencyList__vfunc_22(void) {
    return g_igDependencyList_metaObject_00586768[0];
}
