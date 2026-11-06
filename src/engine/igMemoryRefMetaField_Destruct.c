/* Adds no teardown of its own: the destructor jumps straight to the igRefMetaField destructor. The
 * callee takes the caller's registers untouched, so the thunk has no arguments of its own. */
int igRefMetaField_Destruct();

void igMemoryRefMetaField_Destruct(void) {
    igRefMetaField_Destruct();
}
