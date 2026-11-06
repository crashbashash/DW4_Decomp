/* 0x001e3b50
 * Metaobject accessor of Gap::Core::igActorList: returns the class handle slot
 * g_igActor_metaObject, the "published MetaObject slot" that
 * igActor_Register.c passes to igMetaObject_RegisterClass.
 * This is the slot of the list's element class igActor, not of the list (see vfunc_22).
 * The slot is read through the array extern so the load stays absolute. */
extern int g_igActor_metaObject[4];
int Gap__Core__igActorList__vfunc_24(void) {
    return g_igActor_metaObject[0];
}
