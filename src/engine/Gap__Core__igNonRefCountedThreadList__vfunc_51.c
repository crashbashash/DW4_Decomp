/* 0x003319e0: igNonRefCountedThreadList vtable slot 51, returns the igUnsignedIntMetaField
 * descriptor pointer.  Slot 50 returns the sibling word at 0x00585738 (the metaObject);
 * 0x00585740 is the descriptor filled lazily by igUnsignedIntMetaField_GetDefaultDescriptor via
 * igUnsignedIntMetaField_EnsureRegistered.  Same pattern as the
 * igUnsignedCharMetaField_descriptor at 0x00585768. */
extern int g_igUnsignedIntMetaField_descriptor[4];
int Gap__Core__igNonRefCountedThreadList__vfunc_51(void) {
    return g_igUnsignedIntMetaField_descriptor[0];
}
