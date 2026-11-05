/* 0x003317f0
 * Metaobject accessor in the Gap::Core::igInfoList vtable that returns the cached
 * igMetaObject of igIntMetaField (global named below), not of igInfoList itself;
 * presumably the metaclass of its element/companion type (hypothesis, from
 * the global's name only). */
extern int g_igIntMetaField_metaObject_005860f8[4];
int Gap__Core__igInfoList__vfunc_50(void) {
    return g_igIntMetaField_metaObject_005860f8[0];
}
