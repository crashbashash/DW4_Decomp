/* 0x00325ff0 igPageMemoryPool vtable slot 39: status leaf.  On igMallocMemoryPool this slot sets _elementSize; the page pool accepts the call and stores nothing.
 * Ignores the pool and writes the engine's success-status word (the word at 0x004fb410,
 * zero in the pristine ELF; docs/engine/array-storage.md) through the output-first
 * argument. */
extern int g_statusSucceeded_004fb410[4];
void Gap__Core__igPageMemoryPool__vfunc_39(int *statusOut) {
    *statusOut = g_statusSucceeded_004fb410[0];
}
