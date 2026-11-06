/* 0x001e3740
 * Metaobject accessor of Gap::Core::igBoundingBoxesMaker: returns the class handle slot
 * g_igBoundingBoxesMaker_metaObject, the "published MetaObject slot" that
 * igBoundingBoxesMaker_Register.c passes to igMetaObject_RegisterClass.
 * The slot is read through the array extern so the load stays absolute. */
extern int g_igBoundingBoxesMaker_metaObject[4];
int Gap__Core__igBoundingBoxesMaker__vfunc_22(void) {
    return g_igBoundingBoxesMaker_metaObject[0];
}
