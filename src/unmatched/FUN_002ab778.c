/* 0x002ab778 — FUN_002ab778 (152 bytes). Unless FUN_002ab810 refuses, takes a free slot from FUN_002ab878 (reporting error 0xFF000206 when none is left), creates the handle with FUN_002ab8b8 and records it in DAT_004beadc. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002ab810(void);
int FUN_002ab878(void);
int FUN_002ab8b8(int a, int b);
void FUN_002a0bb8(int obj, int code);

extern int DAT_004beadc[8];

int FUN_002ab778(int a, int b) {
    int *handles = DAT_004beadc;
    int slot;
    int handle;

    if (FUN_002ab810() != 0) {
        return 0;
    }
    slot = FUN_002ab878();
    if (slot == -1) {
        FUN_002a0bb8(0, 0xFF000206);
        return 0;
    }
    handle = FUN_002ab8b8(a, b);
    handles[slot] = handle;
    return handle;
}
