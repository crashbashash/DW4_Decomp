/* When FUN_0027eca8 reports the request flag DAT_004aa750 raised, runs FUN_00273a90 on every
 * active (byte 0 == 1) entry of the 40-entry table DAT_004aa7c0 (72-byte entries) and clears the
 * flag. */
typedef struct Entry_273b58 {
    signed char state;  /* 0x00 */
    char pad1[71];
} Entry_273b58;

extern int DAT_004aa750;
extern Entry_273b58 DAT_004aa7c0[40];
int FUN_0027eca8(int *flag);
void FUN_00273a90(Entry_273b58 *entry);

void FUN_00273b58(void) {
    int i;

    if (FUN_0027eca8(&DAT_004aa750) != 0) {
        for (i = 0; i < 40; i++) {
            if (DAT_004aa7c0[i].state == 1) {
                FUN_00273a90(&DAT_004aa7c0[i]);
            }
        }
        DAT_004aa750 = 0;
    }
}

