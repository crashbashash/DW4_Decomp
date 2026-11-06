/* Takes the first unused entry (byte 0 clear) among the DAT_004a7efc 96-byte entries of
 * DAT_004a7f10 starting at index DAT_004a7ef8, initialises it with FUN_00269ca0 and the four
 * arguments and clears its byte at +74; returns it, or 0 when none is free. */
typedef struct Entry_269e80 {
    signed char used;   /* 0x00 */
    char pad1[73];
    signed char f74; /* 0x4a */
    char pad75[21];
} Entry_269e80;

extern int DAT_004a7ef8;
extern int DAT_004a7efc;
extern Entry_269e80 DAT_004a7f10[];
void FUN_00269ca0(Entry_269e80 *entry, int a, int b, int c, int d);

Entry_269e80 *FUN_00269e80(int a, int b, int c, int d) {
    Entry_269e80 *entry = 0;
    int i;

    for (i = 0; i < DAT_004a7efc; i++) {
        entry = &DAT_004a7f10[DAT_004a7ef8 + i];
        if (entry->used == 0) {
            break;
        }
    }
    if (i == DAT_004a7efc) {
        return 0;
    }
    FUN_00269ca0(entry, a, b, c, d);
    entry->f74 = 0;
    return entry;
}

