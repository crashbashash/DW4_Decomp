/* 0x0018c650
 * igMatrix44fMetaField override of the igMetaField slot at vtable +0x6c (slot 27): returns 16.
 * Same value as the igVec2fMetaField and igVec3fMetaField overrides, so it is not the
 * 64-byte matrix size; 16 is one quadword. Slot role is unpinned (the base
 * returns -1, reference fields 4, and a caller at 0x2f0bc0 uses it as a predicate).
 * The receiver is not read. */
int Gap__Core__igMatrix44fMetaField__vfunc_27(void) {
    return 0x10;
}
