/* 0x0026cbd8 — FUN_0026cbd8 (236 bytes). Re-entrancy-guarded update: unless DAT_004a8e50 is already non-zero, steps it through 1, 2 (FUN_00267058, then FUN_0026ed10 on each of the 16 196-byte entries of DAT_0049c8f8 whose first byte is 1) and 3 (FUN_00265d68, twice while DAT_004a8e58 is below 51) back to 0, all between FUN_0025f2d0 and FUN_0025f2e8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Entry_26cbd8 {
    char used;          /* 0x00 */
    char rest[195];
} Entry_26cbd8;

/* The phase is read and written through a full address held in a register: it is volatile. */
extern volatile int DAT_004a8e50;
extern int DAT_004a8e58;
extern Entry_26cbd8 DAT_0049c8f8[16];
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
void FUN_00267058(void);
void FUN_0026ed10(Entry_26cbd8 *entry);
void FUN_00265d68(void);

void FUN_0026cbd8(void) {
    int i;

    FUN_0025f2d0();
    if (DAT_004a8e50 != 0) {
        FUN_0025f2e8();
        return;
    }
    DAT_004a8e50 = 1;
    FUN_0025f2e8();
    FUN_0025f2d0();
    FUN_00267058();
    DAT_004a8e50 = 2;
    for (i = 0; i < 16; i++) {
        if (DAT_0049c8f8[i].used == 1) {
            FUN_0026ed10(&DAT_0049c8f8[i]);
        }
    }
    DAT_004a8e50 = 3;
    FUN_00265d68();
    if (DAT_004a8e58 < 51) {
        FUN_00265d68();
    }
    DAT_004a8e50 = 0;
    FUN_0025f2e8();
}
