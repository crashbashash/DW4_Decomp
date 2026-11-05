/* 0x00276e50 — FUN_00276e50 (96 bytes). Returns the first unused entry (byte 0 clear) of the 32-entry table DAT_004abc70 (568-byte entries), or 0 when all are in use. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Entry_276e50 {
    signed char used;   /* 0x00 */
    char pad1[567];
} Entry_276e50;         /* 0x238 bytes */

extern Entry_276e50 DAT_004abc70[32];

Entry_276e50 *FUN_00276e50(void) {
    Entry_276e50 *found = 0;
    int i;

    for (i = 0; i < 32; i++) {
        if (DAT_004abc70[i].used == 0) {
            found = &DAT_004abc70[i];
            break;
        }
    }
    return found;
}

