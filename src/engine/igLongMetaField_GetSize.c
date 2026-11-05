/* 0x002ebbf0
 * igLongMetaField vtable slot +0x64 (GetSize): the byte size of one field
 * value.  A "long" field is 8 bytes wide in the reflected layout.  The slot
 * is identified by the field constructor (_size = vtable[0x64]()); the size
 * agrees with the element type (finding #368,
 * config/SLUS-20836/names/MetaFieldSlots.tsv). */
int igLongMetaField_GetSize(void) {
    return 8;
}
