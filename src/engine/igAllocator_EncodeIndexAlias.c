/* 0x002f0650 — alias entry that jumps straight into igAllocator_EncodeIndex (the next function).
 * Retail bytes are a lone `j 0x002f0670` (+ delay-slot nop); the callee takes the
 * caller's registers untouched, so the thunk has no arguments of its own. */
int igAllocator_EncodeIndex();

void igAllocator_EncodeIndexAlias(void) {
    igAllocator_EncodeIndex();
}
