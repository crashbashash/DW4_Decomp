/* 0x00331c60 igLibraryList vtable slot 24: element-class getter.
 * Returns the class handle slot g_igLibrary_metaObject_005860c0 (the "published MetaObject
 * slot" that src/engine/igLibrary_Register.c passes to igMetaObject_RegisterClass), i.e. the
 * igLibrary class an igLibraryList holds. Same slot-24 shape as igViewList and igActorList;
 * see docs/engine/reflection-metadata.md. The slot is read through the array extern so the
 * load stays absolute. */
extern int g_igLibrary_metaObject_005860c0[4];
int Gap__Core__igLibraryList__vfunc_24(void) {
    return g_igLibrary_metaObject_005860c0[0];
}
