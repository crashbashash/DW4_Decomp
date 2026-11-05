/* 0x00277fc0 — FUN_00277fc0 (88 bytes). Returns the first unused entry (byte 0 clear) of the 40-entry table DAT_004b03e8 (56-byte entries), or 0 when all are in use. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Entry_277fc0 {
    signed char used;   /* 0x00 */
    char pad1[55];
} Entry_277fc0;         /* 0x38 bytes */

extern Entry_277fc0 DAT_004b03e8[40];

Entry_277fc0 *FUN_00277fc0(void) {
    Entry_277fc0 *found = 0;
    int i;

    for (i = 0; i < 40; i++) {
        if (DAT_004b03e8[i].used == 0) {
            found = &DAT_004b03e8[i];
            break;
        }
    }
    return found;
}
