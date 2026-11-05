/* 0x0028dac0 — FUN_0028dac0 (88 bytes). Returns the first 256-byte entry of the shared state's table whose state is 1, or 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct Entry0028dac0 {
    int state;            /* +0: 1 = selected by this search */
    char pad4[256 - 4];
};

/* Shared state reached through DAT_004bcc68 (only the members used here). */
struct State0028dac0 {
    char pad0[12];
    int count;                      /* +12 */
    struct Entry0028dac0 entries[1]; /* +16 */
};

extern struct State0028dac0 *DAT_004bcc68;

struct Entry0028dac0 *FUN_0028dac0(void) {
    int count = DAT_004bcc68->count;
    struct Entry0028dac0 *entries = DAT_004bcc68->entries;
    int i;

    for (i = 0; i < count; i++) {
        if (entries[i].state == 1) {
            return &entries[i];
        }
    }
    return 0;
}
