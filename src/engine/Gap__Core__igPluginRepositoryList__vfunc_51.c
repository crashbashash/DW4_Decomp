/* 0x00331920: igPluginRepositoryList vtable slot 51, returns the igRawRefMetaField descriptor
 * pointer.  Slot 50 returns the sibling word at 0x00585a80 (the igRawRefMetaField metaObject,
 * created in FUN_002bbb20); 0x00585a88 is filled lazily by igRawRefMetaField_GetDefaultDescriptor via the
 * igMetaObject_RunStaticInit registration (igRawRefMetaField_EnsureRegistered).  Same pattern as the
 * igUnsignedCharMetaField_descriptor at 0x00585768. */
extern int g_igRawRefMetaField_descriptor[4];
int Gap__Core__igPluginRepositoryList__vfunc_51(void) {
    return g_igRawRefMetaField_descriptor[0];
}
