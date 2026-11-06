/* Counts the tick-down counter 0x004a9b2c down and, when it reaches zero, runs FUN_002734d0 on
 * every active entry (state 1) of the 16-entry table at 0x004a9b30. */
struct Entry68 {          /* 68-byte table entry; only the state byte is read here */
    signed char state;    /* 1 = active */
    char rest[67];
};

extern void FUN_002734d0(struct Entry68 *entry);
extern int DAT_004a9b2c;
extern struct Entry68 DAT_004a9b30[16];

void FUN_002737a8(void) {
    struct Entry68 *entry;
    int i;

    if (--DAT_004a9b2c == 0) {
        entry = DAT_004a9b30;
        for (i = 0; i < 16; i++, entry++) {
            if (entry->state == 1) {
                FUN_002734d0(entry);
            }
        }
    }
}
