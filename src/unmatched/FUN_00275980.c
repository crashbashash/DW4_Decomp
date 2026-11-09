typedef struct AdxTableEntry {
    signed char state;
    char pad1[47];
} AdxTableEntry;

extern AdxTableEntry DAT_004ab650[13];

AdxTableEntry *FUN_00275980(void) {
    AdxTableEntry *found = 0;
    int i;
    for (i = 0; i < 13; i++) {
        if (DAT_004ab650[i].state == 0) {
            found = &DAT_004ab650[i];
        }
    }
    return found;
}
