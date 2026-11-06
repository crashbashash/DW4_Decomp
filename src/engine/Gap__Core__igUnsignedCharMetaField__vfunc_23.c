/* Returns the cached default descriptor of igUnsignedCharMetaField (the word 8 bytes after the
 * class handle). Unlike igUnsignedCharMetaField_GetDefaultDescriptor this virtual method does not
 * register the class when the slot is empty. */
extern int g_igUnsignedCharMetaField_descriptor[4];
int Gap__Core__igUnsignedCharMetaField__vfunc_23(void) {
    return g_igUnsignedCharMetaField_descriptor[0];
}
