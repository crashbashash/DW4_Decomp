/* 0x00267bb8 — FUN_00267bb8 (96 bytes). Returns the first unused entry (byte 0 clear) of the 16-entry table DAT_004a7530 (12-byte entries), or 0 when all are in use. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Entry_267bb8 {
    signed char used;   /* 0x00 */
    char pad1[11];
} Entry_267bb8;         /* 0x0c bytes */

extern Entry_267bb8 DAT_004a7530[16];

Entry_267bb8 *FUN_00267bb8(void) {
    Entry_267bb8 *entry;
    int i;

    for (i = 0; i < 16; i++) {
        entry = &DAT_004a7530[i];
        if (entry->used == 0) {
            break;
        }
    }
    if (i < 16) {
        return entry;
    }
    return 0;
}

