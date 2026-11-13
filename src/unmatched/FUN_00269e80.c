/* Takes the first unused entry (byte 0 clear) among the adxstmf_rtim_num 96-byte entries of
 * DAT_004a7f10 starting at index adxstmf_rtim_ofst, initialises it with ADXSTMF_SetupHandleMember and the four
 * arguments and clears its byte at +74; returns it, or 0 when none is free. */
typedef struct Entry_269e80 {
    signed char used;   /* 0x00 */
    char pad1[73];
    signed char f74; /* 0x4a */
    char pad75[21];
} Entry_269e80;

extern int adxstmf_rtim_ofst;
extern int adxstmf_rtim_num;
extern Entry_269e80 DAT_004a7f10[];
void ADXSTMF_SetupHandleMember(Entry_269e80 *entry, int a, int b, int c, int d);

Entry_269e80 *FUN_00269e80(int a, int b, int c, int d) {
    Entry_269e80 *entry = 0;
    int i;

    for (i = 0; i < adxstmf_rtim_num; i++) {
        entry = &DAT_004a7f10[adxstmf_rtim_ofst + i];
        if (entry->used == 0) {
            break;
        }
    }
    if (i == adxstmf_rtim_num) {
        return 0;
    }
    ADXSTMF_SetupHandleMember(entry, a, b, c, d);
    entry->f74 = 0;
    return entry;
}

