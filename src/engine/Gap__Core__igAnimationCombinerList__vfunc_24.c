/* 0x001e3b60
 * Metaobject accessor of Gap::Core::igAnimationCombinerList: returns the class handle slot
 * g_igAnimationCombiner_metaObject, the "published MetaObject slot" that
 * igAnimationCombiner_Register.c passes to igMetaObject_RegisterClass.
 * This is the slot of the list's element class igAnimationCombiner, not of the list (see vfunc_22).
 * The slot is read through the array extern so the load stays absolute. */
extern int g_igAnimationCombiner_metaObject[4];
int Gap__Core__igAnimationCombinerList__vfunc_24(void) {
    return g_igAnimationCombiner_metaObject[0];
}
