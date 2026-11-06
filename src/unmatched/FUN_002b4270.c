/* Takes an entry from FUN_002b42c8, initialises it with FUN_002b4318, counts it in DAT_004bf010
 * and marks it in use (first word 1); returns it, or null when none is free. */
int *FUN_002b42c8();
int FUN_002b4318();

extern int DAT_004bf010;                  /* count of entries handed out */

int *FUN_002b4270(void) {
    int *entry = FUN_002b42c8();

    if (entry == 0) {
        return 0;
    }
    FUN_002b4318(entry);
    DAT_004bf010++;
    *entry = 1;
    return entry;
}
