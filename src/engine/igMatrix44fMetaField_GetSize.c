/* igMatrix44fMetaField vtable slot +0x64 (GetSize): the byte size of one field value. A 4x4 float
 * matrix is 16 floats * 4 bytes = 0x40. The slot is identified by the field constructor (_size =
 * vtable[0x64]()) and the sizes of all eleven MetaField overrides match their element types. */
int igMatrix44fMetaField_GetSize(void) {
    return 0x40;
}
