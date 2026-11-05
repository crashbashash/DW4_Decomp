/* 0x002d4e70
 * igMetaField slot 27 (+0x6c) for a char array: returns 1, the alignment of a
 * single char element.  Hypothesis for the slot role: igStructMetaField's override
 * returns its reflected `_alignment`, and the array fields return 1 (char),
 * 2 (unsigned short) and 8 (unsigned long), matching their element alignments.
 * Finding 367 leaves the role unpinned; the receiver is not read. */
int Gap__Core__igCharArrayMetaField__vfunc_27(void) {
    return 1;
}
