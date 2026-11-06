/* 0x001e35e0
 * Metaobject accessor of Gap::Core::igAnimationBindingList: returns the class handle slot
 * g_igAnimationSystem_metaObject, the "published MetaObject slot" that
 * igAnimationSystem_Register.c passes to igMetaObject_RegisterClass.
 * This is the slot of igAnimationSystem, not of the binding list; the vtable slot name comes from RTTI.
 * The slot is read through the array extern so the load stays absolute. */
extern int g_igAnimationSystem_metaObject[4];
int Gap__Core__igAnimationBindingList__vfunc_50(void) {
    return g_igAnimationSystem_metaObject[0];
}
