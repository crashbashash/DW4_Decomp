/* Alias entry that jumps straight into igAllocator_EncodeIndex (the next function). The callee
 * takes the caller's registers untouched, so the thunk has no arguments of its own. */
int igAllocator_EncodeIndex();

void igAllocator_EncodeIndexAlias(void) {
    igAllocator_EncodeIndex();
}
