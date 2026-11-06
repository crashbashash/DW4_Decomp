/* 0x00331a30 igContextList vtable slot 24: element-class getter.
 * Returns the class handle slot g_igContext_metaObject (the "published MetaObject
 * slot" that src/engine/igContext_Register.c passes to igMetaObject_RegisterClass), i.e. the
 * igContext class the list holds. Same slot-24 shape as igLibraryList and igViewList;
 * see docs/engine/reflection-metadata.md. The slot is read through the array extern so the
 * load stays absolute. */
extern int g_igContext_metaObject[4];
int Gap__Core__igContextList__vfunc_24(void) {
    return g_igContext_metaObject[0];
}
