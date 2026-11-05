/* 0x0030e8d0
 * Vtable slot 53 of igNonRefCountedThreadList: a constant leaf returning 4.  The list's
 * element type is igUnsignedIntMetaField (slots 50 and 51 hand out that class's metaobject
 * and descriptor), so 4 is read as the element size in bytes.  The receiver is not touched,
 * hence no parameters.  Hypothesis: the slot's role is inferred from the sibling getters
 * and the value, not from a caller. */
int Gap__Core__igNonRefCountedThreadList__vfunc_53(void) {
    return 4;
}
