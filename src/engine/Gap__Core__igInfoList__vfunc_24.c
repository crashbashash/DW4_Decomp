/* 0x00331be0
 * Metaobject accessor in the Gap::Core::igInfoList vtable that returns the cached
 * igMetaObject of igInfo (global named below), not of igInfoList itself;
 * presumably the metaclass of its element/companion type (hypothesis, from
 * the global's name only). */
extern int g_igInfo_metaObject[4];
int Gap__Core__igInfoList__vfunc_24(void) {
    return g_igInfo_metaObject[0];
}
