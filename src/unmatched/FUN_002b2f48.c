/* 0x002b2f48 — FUN_002b2f48 (88 bytes). Takes an entry from FUN_002b2fa0, initialises it with FUN_002b2ff0, counts it in DAT_004beb58 and marks it in use (first word 1); returns it, or null when none is free. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int *FUN_002b2fa0();
int FUN_002b2ff0();

extern int DAT_004beb58;                  /* count of entries handed out */

int *FUN_002b2f48(void) {
    int *entry = FUN_002b2fa0();

    if (entry == 0) {
        return 0;
    }
    FUN_002b2ff0(entry);
    DAT_004beb58++;
    *entry = 1;
    return entry;
}
