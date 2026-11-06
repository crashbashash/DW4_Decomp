/* Returns the igEnumMetaField type descriptor object (created once from the class metaobject and
 * finalised in igEnumMetaField_GetDefaultDescriptor). The slot directly before it (FUN_003317b0)
 * returns the igEnumMetaField class metaobject. */
extern int g_igEnumMetaField_descriptor[4];
int FUN_003317c0(void) {
    return g_igEnumMetaField_descriptor[0];
}
