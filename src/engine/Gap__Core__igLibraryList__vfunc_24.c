/* igLibraryList vtable slot 24: element-class getter. Returns the class handle slot
 * g_igLibrary_metaObject (the "published MetaObject slot" that src/engine/igLibrary_Register.c
 * passes to igMetaObject_RegisterClass), i.e. the igLibrary class an igLibraryList holds. Same
 * slot-24 shape as igViewList and igActorList. The slot is read through the array extern so the
 * load stays absolute. */
extern int g_igLibrary_metaObject[4];
int Gap__Core__igLibraryList__vfunc_24(void) {
    return g_igLibrary_metaObject[0];
}
