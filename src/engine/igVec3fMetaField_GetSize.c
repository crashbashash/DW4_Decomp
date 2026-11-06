/* igMetaField slot +0x64 (GetSize): the byte size of one field value. A Vec3f is three 32-bit
 * floats, 12 bytes. The field constructor stores this result as the field's `_size` (+0x14). */
int igVec3fMetaField_GetSize(void) {
    return 0xC;
}
