/* Updates the block at +3368: adds the step at +684 to the counter at +680 when FUN_002ae4c8
 * allows it, and to +716 when FUN_002ae500 allows it. */
int FUN_002ae4c8();
int FUN_002ae500();

/* The block at +3368 (0xD28) of the owning object. Retail re-reads the counters and never merges or
 * reorders their accesses.
 * matching construct: manual — volatile on the counter members this function needs */
struct Block0D28 {
    char pad[680];
    int f680;                    /* counter advanced by f684 (FUN_002ae458) */
    volatile int f684;                    /* step */
    char pad688[716 - 688];
    int f716;                    /* counter advanced by f684; -1 = off, negative = due (FUN_002af998) */
    int f720;
    int f724;                             /* enable value (FUN_002aee00) */
    char pad728[732 - 728];
    int f732;
    char pad736[740 - 736];
    int f740;
    int f744;
};

void FUN_002ae458(char *obj) {
    struct Block0D28 *block = (struct Block0D28 *)(obj + 3368);

    if (FUN_002ae4c8(obj) != 0) {
        block->f680 += block->f684;
    }
    if (FUN_002ae500(obj, block) != 0) {
        block->f716 += block->f684;
    }
}
