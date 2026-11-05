/* 0x00331510
 * igMallocMemoryPool vtable slot 26: constant-zero leaf (`jr ra; move v0,zero`,
 * asm/Gap__Core__igMallocMemoryPool__vfunc_26.s). The igPageMemoryPool override of this
 * slot (0x00325d30) also returns 0, while igStackMemoryPool slot 26 returns its
 * `_rawMemory` field, so the slot is a per-pool accessor whose Malloc value is "none".
 * The receiver is not read. */
int Gap__Core__igMallocMemoryPool__vfunc_26(void) {
    return 0;
}
