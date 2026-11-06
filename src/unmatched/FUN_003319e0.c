/* IgNonRefCountedThreadList vtable slot 51, returns the igUnsignedIntMetaField descriptor pointer.
 * Slot 50 returns the metaObject; the descriptor is filled lazily by
 * igUnsignedIntMetaField_GetDefaultDescriptor via igUnsignedIntMetaField_EnsureRegistered. Same
 * pattern as igUnsignedCharMetaField_descriptor. */
extern int g_igUnsignedIntMetaField_descriptor[4];
int FUN_003319e0(void) {
    return g_igUnsignedIntMetaField_descriptor[0];
}
