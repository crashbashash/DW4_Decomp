/* Bumps the counter at the head of DAT_004bea88 and calls FUN_002ae408 on each of its eight slot
 * objects whose word at +76 is set. */
int FUN_002ae408();

struct SlotObj {
    char pad[76];
    int f76;                              /* non-zero: the slot is processed */
};

/* DAT_004bea88: a counter, two words (+8 read by FUN_002af998) and, at +84, eight object slots (FUN_002ae398). */
struct SlotObj;

struct SlotTable {
    int counter;
    int f4;
    int f8;
    char pad12[84 - 12];
    struct SlotObj *slots[8];             /* +84 */
};

extern struct SlotTable DAT_004bea88;

void FUN_002ae398(void) {
    int i;

    DAT_004bea88.counter++;
    for (i = 0; i < 8; i++) {
        struct SlotObj *obj = DAT_004bea88.slots[i];

        if (obj != 0 && obj->f76 != 0) {
            FUN_002ae408(obj);
        }
    }
}
