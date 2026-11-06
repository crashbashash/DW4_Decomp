/* Element size in bytes of the list's items: 0x28 (one igCharMetrics record). The same class's
 * TrimCapacity (vfunc_18) re-sizes the buffer with List_Reserve(self, count, 0x28), and the
 * sibling lists igDependencyList (8) and igPsx2AudioSourceList (0x24) return their item size from
 * this same slot 23. */
#define CHAR_METRICS_ITEM_SIZE 0x28
int Gap__Core__igCharMetricsList__vfunc_23(void) {
    return CHAR_METRICS_ITEM_SIZE;
}
