void igTimeAttr_apply(igTimeAttr *self, void *arg1) {
    *(long long *)((char *)(arg1) + 96) = (long long) self->_time;
}

/* Take the 64-bit time stored at +96 of `source` (an object not typed in reflected.h) as this
 * attribute's `_time`. */

void igTimeAttr_SynchronizeDefault(igTimeAttr *self, void *source) {
    self->_time = (long long) *(long long *)((char *)(source) + 96);
}

