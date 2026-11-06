/* igMetaField slot +0x64 (GetSize): the byte size of one field value. An unsigned char is a single
 * byte. The field constructor stores this result as the field's `_size` (+0x14). */
int igUnsignedCharMetaField_GetSize(void) {
    return 1;
}
