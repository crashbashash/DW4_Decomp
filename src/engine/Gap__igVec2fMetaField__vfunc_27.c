/* Override of the igMetaField slot at vtable +0x6c (slot 27): returns 16, one quadword rather than
 * the 8-byte element size. The receiver is not read. */
int Gap__igVec2fMetaField__vfunc_27(void) {
    return 0x10;
}
