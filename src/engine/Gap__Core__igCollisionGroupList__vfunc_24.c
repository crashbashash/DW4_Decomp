/* igCollisionGroupList vtable slot 24: element-class getter. Returns the class handle slot
 * g_igCollisionGroup_metaObject (the "published MetaObject slot" that
 * src/engine/igCollisionGroup_Register.c passes to igMetaObject_RegisterClass), i.e. the
 * igCollisionGroup class the list holds. Same slot-24 shape as igLibraryList and igViewList. The
 * slot is read through the array extern so the load stays absolute. */
extern int g_igCollisionGroup_metaObject[4];
int Gap__Core__igCollisionGroupList__vfunc_24(void) {
    return g_igCollisionGroup_metaObject[0];
}
