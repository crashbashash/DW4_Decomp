/* 0x0018e2e0
 * igMetaField slot +0x64 (GetSize): the byte size of one field value.  A Vec2f is
 * two 32-bit floats, 8 bytes.  The field constructor 0x2fc630 stores this
 * result as the field's `_size` (+0x14); finding #368. */
int igVec2fMetaField_GetSize(void) {
    return 8;
}
