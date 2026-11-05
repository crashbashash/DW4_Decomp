/* 0x00331a50
 * Element size in bytes of the list's items: 8.  The same class's TrimCapacity
 * (vfunc_18, 0x00331e80) re-sizes the buffer with List_Reserve(self, count, 8), and
 * the sibling lists igCharMetricsList (0x28) and igPsx2AudioSourceList (0x24) return their
 * item size from this same slot 23. */
int Gap__Core__igDependencyList__vfunc_23(void) {
    return 8;
}
