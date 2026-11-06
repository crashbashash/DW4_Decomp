/* returns the igEnumMetaField type descriptor object (created once from the class metaobject at
 * 0x00586598 and finalised in igEnumMetaField_GetDefaultDescriptor). The RTTI label
 * "igDirectoryList" is inherited from the neighbouring vtable run; the slot directly before it
 * (vfunc_50) returns the igEnumMetaField class metaobject, so this is the igEnumMetaField
 * "descriptor" getter. */
extern int g_igEnumMetaField_descriptor[4];
int Gap__Core__igDirectoryList__vfunc_51(void) {
    return g_igEnumMetaField_descriptor[0];
}
