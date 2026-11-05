/* 0x0028d760 — FUN_0028d760 (140 bytes). Installs the stream work area at 0x004bcc68: clears count * 64 + 4
   bytes of it (FUN_0028b530), initialises it (FUN_0028d868), records the stream count (+12) and marks every
   stream entry (256 bytes from +16) with state 1. Returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct StreamEntry28d {
    int state;          /* +0: 1 = free */
    char pad4[252];
};

struct StreamWork28d {
    char pad0[12];
    int count;                          /* +12 */
    struct StreamEntry28d entries[1];   /* +16 */
};

extern void FUN_0028b530(void *dest, int value, int size);
extern void FUN_0028d868(struct StreamWork28d *work);
extern struct StreamWork28d *DAT_004bcc68;

int FUN_0028d760(int count, struct StreamWork28d *work) {
    struct StreamEntry28d *entry;
    int remaining;

    DAT_004bcc68 = work;
    FUN_0028b530(work, 0, count * 64 + 4);
    FUN_0028d868(DAT_004bcc68);
    DAT_004bcc68->count = count;
    entry = DAT_004bcc68->entries;
    if (count > 0) {
        remaining = count;
        do {
            entry->state = 1;
            entry++;
        } while (--remaining != 0);
    }
    return 0;
}
