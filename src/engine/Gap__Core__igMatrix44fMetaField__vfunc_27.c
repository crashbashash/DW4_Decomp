/* Override of the igMetaField slot at vtable +0x6c (slot 27): returns 16, one quadword rather than
 * the 64-byte matrix size. The receiver is not read. */
int Gap__Core__igMatrix44fMetaField__vfunc_27(void) {
    return 0x10;
}
