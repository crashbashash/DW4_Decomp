/* Output-first status wrapper. The status word is returned through the hidden output pointer (a0).
 * The shared helper also reads a1 (the pool) and a2 (a request descriptor) from its asm, and this
 * wrapper passes both through untouched, which is why only the local cell is named at the call.
 * The helper leaves the success word (g_statusSucceeded) in the cell. */
int FUN_002f0880(int *);

void Gap__Core__igAliasMemoryPool__vfunc_45(int *outStatus) {
    int status;

    FUN_002f0880(&status);
    *outStatus = status;
}
