/* IgPluginRepositoryList vtable slot 51, returns the igRawRefMetaField descriptor pointer. Slot 50
 * returns the igRawRefMetaField metaObject; the descriptor is filled lazily by
 * igRawRefMetaField_GetDefaultDescriptor via the igMetaObject_RunStaticInit registration
 * (igRawRefMetaField_EnsureRegistered). */
extern int g_igRawRefMetaField_descriptor[4];
int Gap__Core__igPluginRepositoryList__vfunc_51(void) {
    return g_igRawRefMetaField_descriptor[0];
}
