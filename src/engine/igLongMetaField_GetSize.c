/* igLongMetaField vtable slot +0x64 (GetSize): the byte size of one field value. A "long" field is
 * 8 bytes wide in the reflected layout. The slot is identified by the field constructor (_size =
 * vtable[0x64]()); the size agrees with the element type. */
int igLongMetaField_GetSize(void) {
    return 8;
}
