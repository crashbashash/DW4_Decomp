/* 0x0030f030
 * igVirtualCFuncMetaField override of the igMetaField slot at vtable +0x6c (slot 27): returns 4.
 * Base igMetaField returns -1 and the ref fields also return 4 (finding 367, where the role
 * of this slot is left unpinned: a caller at 0x2f0bc0 uses it as a predicate). The
 * receiver is not read. */
int Gap__Core__igVirtualCFuncMetaField__vfunc_27(void) {
    return 4;
}
