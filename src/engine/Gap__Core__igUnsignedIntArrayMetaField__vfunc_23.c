/* 0x00331040
 * Returns the cached default descriptor of igUnsignedIntArrayMetaField, the
 * word 8 bytes after the class handle 0x585748 (same slot layout as the
 * descriptor getters in list-metadata-access.c).  No lazy registration here. */
extern int g_igUnsignedIntArrayMetaField_descriptor[4];
int Gap__Core__igUnsignedIntArrayMetaField__vfunc_23(void) {
    return g_igUnsignedIntArrayMetaField_descriptor[0];
}
