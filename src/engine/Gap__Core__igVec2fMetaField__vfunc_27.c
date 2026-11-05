/* 0x0018e300
 * igVec2fMetaField override of the igMetaField slot at vtable +0x6c (slot 27): returns 16.
 * The sibling GetSize (slot 25, 0x18e2e0) returns the 8-byte element size, so this is not
 * the size; 16 is one quadword. Slot role is unpinned (finding 367: base returns -1, ref
 * fields 4, and a caller at 0x2f0bc0 uses it as a predicate). The receiver is not read. */
int Gap__Core__igVec2fMetaField__vfunc_27(void) {
    return 0x10;
}
