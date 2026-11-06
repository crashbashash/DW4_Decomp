/* 0x001e3520
 * Metaobject accessor of Gap::Core::igActorList: returns the class handle slot
 * g_igActorList_metaObject, the "published MetaObject slot" that
 * igActorList_Register.c passes to igMetaObject_RegisterClass.
 * The slot is read through the array extern so the load stays absolute. */
extern int g_igActorList_metaObject[4];
int Gap__Core__igActorList__vfunc_22(void) {
    return g_igActorList_metaObject[0];
}
