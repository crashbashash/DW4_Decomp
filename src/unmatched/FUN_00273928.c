/* Runs FUN_00273558 on every active entry (state 1) of the 16-entry table at 0x004a9b30, bracketed
 * by FUN_0027b2b0 / FUN_0027b2c8. */
struct Entry68 {          /* 68-byte table entry; only the state byte is read here */
    signed char state;    /* 1 = active */
    char rest[67];
};

extern void FUN_0027b2b0(void);
extern void FUN_0027b2c8(void);
extern void FUN_00273558(struct Entry68 *entry);
extern struct Entry68 DAT_004a9b30[16];

void FUN_00273928(void) {
    struct Entry68 *entry;
    int i;

    FUN_0027b2b0();
    entry = DAT_004a9b30;
    for (i = 0; i < 16; i++, entry++) {
        if (entry->state == 1) {
            FUN_00273558(entry);
        }
    }
    FUN_0027b2c8();
}
