/* 0x002b1700 — FUN_002b1700 (144 bytes). One-time initialisation: on the first call bumps DAT_0058569c, stores FUN_002b16e0's result in DAT_00585688, initialises the `count` 16-byte entries at `entries` (FUN_002b1920) and registers them with the list at DAT_00585690 (FUN_002b18e0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b16e0(void);
void FUN_002b1920(int count, void *entries);
void FUN_002b18e0(void *list, int count, void *entries);

extern int DAT_0058569c;
extern int DAT_00585688;
extern char DAT_00585690[];

void FUN_002b1700(int count, void *entries) {
    int *handle;

    if (DAT_0058569c > 0) {
        return;
    }
    DAT_0058569c++;
    /* matching construct: the result address is taken into a local before the call */
    handle = &DAT_00585688;
    *handle = FUN_002b16e0();
    FUN_002b1920(count, entries);
    FUN_002b18e0(DAT_00585690, count, entries);
}
