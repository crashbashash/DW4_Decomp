/* 0x002b3858 — FUN_002b3858 (88 bytes). While the counter DAT_004bec20 is positive, runs FUN_002b4268, FUN_002b2f40, FUN_002b4098 and FUN_00283090 once and decrements it. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b2f40();
int FUN_002b4098();
int FUN_002b4268();
/* matching construct: manual — FUN_00283090 declared void (its result is unused) leaves v0 free for the decrement, as in retail */
void FUN_00283090();

extern int DAT_004bec20;

void FUN_002b3858(void) {
    if (DAT_004bec20 > 0) {
        FUN_002b4268();
        FUN_002b2f40();
        FUN_002b4098();
        FUN_00283090();
        DAT_004bec20--;
    }
}
