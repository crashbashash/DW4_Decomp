/* 0x002ae528 — FUN_002ae528 (72 bytes). Sets the block's word at +720 from +680 when FUN_002adc40(handle, 71) is 1, else from +732. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002adc40();

/* The block at +3368 (0xD28) of the owning object. Retail re-reads the counters and never merges or
 * reorders their accesses, so they are volatile here (FUN_002ae458, FUN_002ae500, FUN_002ae528,
 * FUN_002af998); making the plain members volatile breaks FUN_002ae528 and FUN_002aee00.
 * matching construct: manual — volatile on the counter members */
struct Block0D28 {
    char pad[680];
    volatile int f680;                    /* counter advanced by f684 (FUN_002ae458) */
    volatile int f684;                    /* step */
    char pad688[716 - 688];
    volatile int f716;                    /* counter advanced by f684; -1 = off, negative = due (FUN_002af998) */
    int f720;
    int f724;                             /* enable value (FUN_002aee00) */
    char pad728[732 - 728];
    volatile int f732;
    char pad736[740 - 736];
    int f740;
    int f744;
};

void FUN_002ae528(int handle, struct Block0D28 *block) {
    if (FUN_002adc40(handle, 71) == 1) {
        block->f720 = block->f680;
    } else {
        block->f720 = block->f732;
    }
}
