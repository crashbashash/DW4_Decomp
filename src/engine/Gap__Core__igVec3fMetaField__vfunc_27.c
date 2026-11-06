/* 0x0018e480
 * igVec3fMetaField override of the igMetaField slot at vtable +0x6c (slot 27): returns 16.
 * The sibling GetSize (slot 25, 0x18e460) returns the 12-byte element size, so this is not
 * the size; 16 is one quadword. Slot role is unpinned (base returns -1, ref
 * fields 4, and a caller at 0x2f0bc0 uses it as a predicate). The receiver is not read. */
int Gap__Core__igVec3fMetaField__vfunc_27(void) {
    return 0x10;
}
