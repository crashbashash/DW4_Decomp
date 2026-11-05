/* 0x002b3058 — FUN_002b3058 (60 bytes). Passes the entry's three parameter words and the caller's value to FUN_002846c0, then clears the entry's word at +4. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002846c0();

struct EntryParams {
    int f0;
    int f4;
    int f8;
};

/* Layout shared with FUN_002b2ff0, which initialises it. */
struct Entry18 {
    int inUse;
    int f4;
    struct EntryParams params;            /* +8 */
    unsigned char bytes[3];               /* +20 */
};

void FUN_002b3058(struct Entry18 *entry, int unused, int value) {
    struct EntryParams *params = &entry->params;

    FUN_002846c0(params->f0, params->f4, params->f8, value);
    entry->f4 = 0;
}
