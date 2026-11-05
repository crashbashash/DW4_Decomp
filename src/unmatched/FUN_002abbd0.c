/* 0x002abbd0 — FUN_002abbd0 (96 bytes). Clears a 48-byte block, then resets its five 32-byte entries and the trailer at +160 with FUN_002afba8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdEntry32 {
    char pad0[32];
} SfdEntry32;

typedef struct SfdTable {
    SfdEntry32 entries[5];
    char trailer[4];        /* +160 */
} SfdTable;

extern void FUN_0028b530(void *dst, int value, int size);
extern void FUN_002afba8(void *entry);

void FUN_002abbd0(SfdTable *table) {
    SfdEntry32 *entry;
    int i;

    FUN_0028b530(table, 0, 48);
    entry = table->entries;
    for (i = 4; i >= 0; i--) {
        FUN_002afba8(entry++);
    }
    FUN_002afba8(table->trailer);
}
