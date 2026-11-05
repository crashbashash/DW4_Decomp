/* 0x002ce830
 * Vtable slot 25 of igMemoryDescriptorMetaField: the byte size of the field's storage.
 * The array metafields return `_num * element size` from this slot (igEnumArrayMetaField
 * 0x002dc720, igUnsignedLongArrayMetaField 0x0030ea50, truncated to the reflected 16-bit
 * `_size`); a memory descriptor stores a single 32-bit reference, so it returns 4.  The
 * receiver is not touched, hence no parameters. */
int Gap__Core__igMemoryDescriptorMetaField__vfunc_25(void) {
    return 4;
}
