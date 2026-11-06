/* IgNonRefCountedThreadList vtable slot 51, returns the igUnsignedIntMetaField descriptor pointer.
 * Slot 50 returns the metaObject; the descriptor is filled lazily by
 * igUnsignedIntMetaField_GetDefaultDescriptor via igUnsignedIntMetaField_EnsureRegistered. Same
 * pattern as igUnsignedCharMetaField_descriptor. */
extern int g_igUnsignedIntMetaField_descriptor[4];
int Gap__Core__igNonRefCountedThreadList__vfunc_51(void) {
    return g_igUnsignedIntMetaField_descriptor[0];
}
