/* 0x00331520
 * igMallocMemoryPool vtable slot 29: constant-zero leaf (`jr ra; move v0,zero`,
 * asm/Gap__Core__igMallocMemoryPool__vfunc_29.s). The igPageMemoryPool (0x00325d60) and
 * igStackMemoryPool (0x00330f80) overrides of this slot return 1, so it reads as a
 * yes/no pool property that the malloc-backed pool answers "no". Role not recovered;
 * the receiver is not read. */
int Gap__Core__igMallocMemoryPool__vfunc_29(void) {
    return 0;
}
