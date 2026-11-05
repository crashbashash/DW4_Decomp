/* 0x00275408 — FUN_00275408 (80 bytes). Returns 1 when any of the 13 48-byte entries of DAT_004ab650 is active (byte 0 == 1) in state 2 (byte 2), else 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Entry_275408 {
    signed char active;     /* 0x00 */
    char pad1;
    signed char state;      /* 0x02 */
    char pad3[45];
} Entry_275408;             /* 0x30 bytes */

extern Entry_275408 DAT_004ab650[13];

int FUN_00275408(void) {
    int i;

    for (i = 0; i < 13; i++) {
        if (DAT_004ab650[i].active == 1 && DAT_004ab650[i].state == 2) {
            return 1;
        }
    }
    return 0;
}
