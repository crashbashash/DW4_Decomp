/* True when the block's word at +716 is not -1 and the object's state word at +76 is 4. */

struct Obj004C {
    char pad[76];
    int f76;
};

/* The block at +3368 (0xD28) of the owning object. Retail re-reads the counters and never merges or
 * reorders their accesses.
 * matching construct: manual — volatile on the counter members this function needs */
struct Block0D28 {
    char pad[680];
    int f680;                    /* counter advanced by f684 (FUN_002ae458) */
    int f684;                    /* step */
    char pad688[716 - 688];
    volatile int f716;                    /* counter advanced by f684; -1 = off, negative = due (FUN_002af998) */
    int f720;
    int f724;                             /* enable value (FUN_002aee00) */
    char pad728[732 - 728];
    int f732;
    char pad736[740 - 736];
    int f740;
    int f744;
};

int FUN_002ae500(struct Obj004C *obj, struct Block0D28 *block) {
    if (block->f716 == -1) {
        return 0;
    }
    return obj->f76 == 4;
}
