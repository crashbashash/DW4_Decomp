/* 0x00331250
 * Class-handle getter: returns the cached metaobject pointer held in the
 * global at 0x585e98 (same accessor idiom as the other `*_metaObject_<addr>`
 * getters in this folder). */
extern int g_igMemoryPoolContextInfo_metaObject_00585e98[4];
int Gap__Core__igMemoryPoolContextInfo__vfunc_50(void) {
    return g_igMemoryPoolContextInfo_metaObject_00585e98[0];
}
