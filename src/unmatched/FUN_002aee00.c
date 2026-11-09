/* Checked setter (error 0xFF000129): stores three parameters into the block at +3368 and
 * reconfigures FUN_002ada78 entries 15 and 71 — (15,5)/(71,0) when enabling, (71,1)/(15,1) when
 * clearing. */
int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002ada78();

/* The block at +3368 (0xD28) of the owning object. Retail re-reads the counters and never merges or
 * reorders their accesses. */
struct Block0D28 {
    char pad[680];
    int f680;                    /* counter advanced by f684 (FUN_002ae458) */
    int f684;                    /* step */
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

/* FUN_002a0dd8(handle) records the handle in a global and returns -1 when it is null or its word
 * at +72 is clear. */
int FUN_002aee00(char *handle, int enable, int arg2, int arg3) {
    struct Block0D28 *block;

    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF000129);
    }
    block = (struct Block0D28 *)(handle + 3368);
    if (enable != 0) {
        block->f724 = enable;
        block->f740 = arg2;
        block->f744 = arg3;
        FUN_002ada78(handle, 15, 5);
        FUN_002ada78(handle, 71, 0);
    } else {
        FUN_002ada78(handle, 71, 1);
        FUN_002ada78(handle, 15, 1);
        block->f744 = arg3;
        block->f740 = arg2;
        block->f724 = 0;
    }
    return 0;
}
