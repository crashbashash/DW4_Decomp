/* Adds no teardown of its own: the destructor jumps straight to the igMetaField base destructor.
 * The callee takes the caller's registers untouched, so the thunk has no arguments of its own. */
int igMetaField_Destruct();

void igRefMetaField_Destruct(void) {
    igMetaField_Destruct();
}
