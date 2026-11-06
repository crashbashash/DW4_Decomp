/* Unless mode DAT_004b1dc8 is 1 with no pending count in DAT_004b1dc0: between FUN_0027b270 and
 * FUN_0027b288, runs FUN_0027ab08 on every active (byte 0 == 1) entry of the 16-entry table
 * DAT_004b4220 (100-byte entries), then calls FUN_00272d60 and FUN_0027dd58. */
typedef struct Entry_27acc8 {
    signed char state;  /* 0x00 */
    char pad1[99];
} Entry_27acc8;         /* 0x64 bytes */

extern int DAT_004b1dc8;
extern int DAT_004b1dc0;
extern Entry_27acc8 DAT_004b4220[16];
void FUN_0027b270(void);
void FUN_0027b288(void);
void FUN_0027ab08(Entry_27acc8 *entry);
void FUN_00272d60(void);
void FUN_0027dd58(void);

void FUN_0027acc8(void) {
    int i;

    if (DAT_004b1dc8 == 1 && DAT_004b1dc0 <= 0) {
        return;
    }
    FUN_0027b270();
    for (i = 0; i < 16; i++) {
        if (DAT_004b4220[i].state == 1) {
            FUN_0027ab08(&DAT_004b4220[i]);
        }
    }
    FUN_0027b288();
    FUN_00272d60();
    FUN_0027dd58();
}

