/* For each of the 32 16-byte entries of DAT_0056e220, calls the first function of the table its
 * first word points at, when both are set. */
typedef struct Callbacks_270220 {
    void (*run)(void);  /* 0x00 */
} Callbacks_270220;

typedef struct Entry_270220 {
    Callbacks_270220 *callbacks;    /* 0x00 */
    char rest[12];
} Entry_270220;

extern Entry_270220 DAT_0056e220[32];

void FUN_00270220(void) {
    int i;

    for (i = 0; i < 32; i++) {
        if (DAT_0056e220[i].callbacks != 0 && DAT_0056e220[i].callbacks->run != 0) {
            DAT_0056e220[i].callbacks->run();
        }
    }
}
