/* 0x003275e0 — igStackMemoryPool slot 45: output-first status wrapper.
 * The status word is returned through the hidden output pointer (a0).  The
 * shared helper FUN_002f0880 also reads a1 (the pool) and a2 (a request
 * descriptor) from its asm, and this wrapper passes both through untouched,
 * which is why only the local cell is named at the call.  The helper leaves
 * the success word (g_statusSucceeded_004fb410) in the cell; see
 * docs/engine/allocator-builder.md.  igAliasMemoryPool slot 45 has the same body. */
int FUN_002f0880(int *);

void Gap__Core__igStackMemoryPool__vfunc_45(int *outStatus) {
    int status;

    FUN_002f0880(&status);
    *outStatus = status;
}
