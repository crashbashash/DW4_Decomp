/* 0x00331060
 * Returns the cached default descriptor of igUnsignedCharMetaField (the word
 * 8 bytes after the class handle 0x585760).  Unlike
 * igUnsignedCharMetaField_GetDefaultDescriptor in list-metadata-access.c this
 * virtual method does not register the class when the slot is empty. */
extern int g_igUnsignedCharMetaField_descriptor_00585768[4];
int Gap__Core__igUnsignedCharMetaField__vfunc_23(void) {
    return g_igUnsignedCharMetaField_descriptor_00585768[0];
}
