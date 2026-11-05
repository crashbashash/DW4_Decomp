/* 0x002796b0 — FUN_002796b0 (116 bytes). Claims the first unused entry (byte 0 clear) among the DAT_004b1dc0 24-byte entries of DAT_004b1e20, marking it used; returns it, or 0 when none is free. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Entry_2796b0 {
    signed char used;   /* 0x00 */
    char pad1[23];
} Entry_2796b0;         /* 0x18 bytes */

extern int DAT_004b1dc0;
extern Entry_2796b0 DAT_004b1e20[];

Entry_2796b0 *FUN_002796b0(void) {
    Entry_2796b0 *entry = 0;
    int i;

    for (i = 0; i < DAT_004b1dc0; i++) {
        entry = &DAT_004b1e20[i];
        if (entry->used == 0) {
            break;
        }
    }
    if (i == DAT_004b1dc0) {
        return 0;
    }
    entry->used = 1;
    return entry;
}

