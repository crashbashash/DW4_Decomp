void Gap__Attrs__igTimeAttr__vfunc_24(void *arg0, void *arg1) {
    *(long long *)((char *)(arg1) + 96) = (long long) *(long long *)((char *)(arg0) + 16);
}

/* Take the 64-bit time stored at +96 of `source` (an object not typed in reflected.h) as this
 * attribute's `_time`. */

void Gap__Attrs__igTimeAttr__vfunc_26(igTimeAttr *self, void *source) {
    self->_time = (long long) *(long long *)((char *)(source) + 96);
}

