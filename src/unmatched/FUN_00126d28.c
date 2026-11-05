/* 0x00126d28 — FUN_00126d28 (204 bytes). Under the library lock, stores a 64-bit value into one of two settings for keys -1/-2, accepts key -3, answers key -4 with whether the value is zero, and returns 0 for any other key. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00127310(void *reent);
void FUN_00127390(void *reent);
extern long DAT_004858b8;
extern long DAT_004858c0;

int FUN_00126d28(void *reent, int key, long value) {
    FUN_00127310(reent);
    switch (key) {
    case -1:
        DAT_004858b8 = value;
        FUN_00127390(reent);
        return 1;
    case -2:
        DAT_004858c0 = value;
        FUN_00127390(reent);
        return 1;
    case -3:
        FUN_00127390(reent);
        return 1;
    case -4:
        FUN_00127390(reent);
        return value == 0;
    }
    FUN_00127390(reent);
    return 0;
}
