/* 0x002af998 — FUN_002af998 (116 bytes). Reports through *out whether the block at +3368 is due: a negative word at +716 is reset to 0 and counts as due; otherwise FUN_00285118(arg1, arg2, f716, DAT_004bea88 word +8, block) decides. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00285118();

/* DAT_004bea88: a counter, two words (+8 read by FUN_002af998) and, at +84, eight object slots (FUN_002ae398). */
struct SlotObj;

struct SlotTable {
    int counter;
    int f4;
    int f8;
    char pad12[84 - 12];
    struct SlotObj *slots[8];             /* +84 */
};

extern struct SlotTable DAT_004bea88;

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

void FUN_002af998(char *obj, int arg1, int arg2, int *out) {
    int result;
    struct Block0D28 *block = (struct Block0D28 *)(obj + 3368);
    int negative;
    struct SlotTable *table = &DAT_004bea88;

    negative = block->f716 < 0;
    /* matching construct: permuter — the do/while(0) wrapper (a macro-style block) and this declaration order give retail's t0/v0 allocation */
    do {
        if (negative) {
            block->f716 = 0;
            *out = 1;
            return;
        }
    } while (0);
    result = FUN_00285118(arg1, arg2, block->f716, table->f8, block);
    if (result != 0) {
        *out = 1;
        return;
    }
    *out = 0;
}
