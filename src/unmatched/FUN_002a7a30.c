/* Initialises \`count\` 232-byte slots, taking each slot's id from \`ids\`. */
typedef struct SfdSlot {
    int f0;
    int f4;
    int id;                 /* +8 */
    char sub12[44];         /* +12, reset by FUN_002ae248 */
    int f56;
    int f60;
    int f64;
    int f68;
    int f72;
    int f76;
    int f80;
    char pad84[4];
    char mask88[136];       /* +88, filled by FUN_002a7ad0 */
    int f224;
    int pad228;
} SfdSlot;

extern void FUN_002ae248(void *sub, int value);
extern void FUN_002a7ad0(void *mask);

void FUN_002a7a30(SfdSlot *slot, int *ids, int count) {
    if (count > 0) {
        int *id = ids;
        int remaining = count;

        do {
            slot->f0 = 0;
            slot->f4 = 0;
            FUN_002ae248(slot->sub12, 0);
            slot->id = *id++;
            slot->f56 = 0;
            slot->f60 = 1;
            slot->f64 = 0;
            slot->f68 = 0;
            slot->f72 = 0;
            slot->f76 = 0;
            slot->f80 = 0;
            FUN_002a7ad0(slot->mask88);
            slot->f224 = 0;
            slot++;
        } while (--remaining != 0);
    }
}
