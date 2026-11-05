/* 0x0018e660
 * igMetaField slot +0x64 (GetSize): the byte size of one field value.  A Vec4f is
 * four 32-bit floats, 16 bytes.  The field constructor 0x2fc630 stores this
 * result as the field's `_size` (+0x14); finding #368. */
int igVec4fMetaField_GetSize(void) {
    return 0x10;
}
