/* When FUN_0027eca8 reports the request flag DAT_004ab5e4 raised, runs FUN_00275520 on every
 * active (byte 0 == 1) entry of the 13-entry table DAT_004ab650 (48-byte entries) and clears the
 * flag. */
typedef struct Entry_2755e8 {
    signed char state;  /* 0x00 */
    char pad1[47];
} Entry_2755e8;

extern int DAT_004ab5e4;
extern Entry_2755e8 DAT_004ab650[13];
int FUN_0027eca8(int *flag);
void FUN_00275520(Entry_2755e8 *entry);

void FUN_002755e8(void) {
    int i;

    if (FUN_0027eca8(&DAT_004ab5e4) != 0) {
        for (i = 0; i < 13; i++) {
            if (DAT_004ab650[i].state == 1) {
                FUN_00275520(&DAT_004ab650[i]);
            }
        }
        DAT_004ab5e4 = 0;
    }
}

