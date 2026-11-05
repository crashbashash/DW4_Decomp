/* 0x002b3130 — FUN_002b3130 (20 bytes). Stores the three byte arguments into the entry's byte triple at +20. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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

void FUN_002b3130(struct Entry18 *entry, unsigned char b0, unsigned char b1, unsigned char b2) {
    unsigned char *bytes = entry->bytes;

    bytes[0] = b0;
    bytes[1] = b1;
    bytes[2] = b2;
}
