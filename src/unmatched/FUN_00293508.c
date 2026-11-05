/* 0x00293508 — FUN_00293508 (160 bytes). Allocates `size` bytes for the Sofdec work area (its error string names it MWSFD_Malloc): refuses once 32 blocks are held, allocates through FUN_002935a8 or FUN_002935e0 depending on the +512 mode word, and records each block in the +532 table. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void *FUN_002935a8(void *work, int size);
extern void *FUN_002935e0(int size);
extern void FUN_00293708(void *work);
extern void FUN_0029a320(const char *msg);
extern char DAT_004f3070[]; /* "E2053001 MWSFD_Malloc: cnt over." */

typedef struct {
    char pad0[512];
    int mode;           /* 512: selects the allocator */
    char pad516[12];
    int count;          /* 528: blocks held */
    void *blocks[32];   /* 532 */
} Work293508;

void *FUN_00293508(Work293508 *work, int size) {
    void *block;

    if (work->count >= 32) {
        FUN_0029a320(DAT_004f3070);
        return 0;
    }
    if (size < 0) {
        return 0;
    }
    if (work->mode != 0) {
        block = FUN_002935a8(work, size);
    } else {
        block = FUN_002935e0(size);
    }
    if (block != 0) {
        work->blocks[work->count] = block;
        FUN_00293708(work);
    }
    return block;
}
