/* published MetaObject accessor of Gap::Core::igLibraryList. A 12-byte leaf (lui/lw) that returns
 * the class handle slot g_igLibraryList_metaObject, the "published MetaObject slot" passed to
 * igMetaObject_RegisterClass in src/engine/igLibraryList_Register.c; the same shape as
 * igObjectList_GetPublishedMetaObject (rule `published-accessor`). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igLibraryList_metaObject[4];
int Gap__Core__igLibraryList__vfunc_22(void) {
    return g_igLibraryList_metaObject[0];
}
