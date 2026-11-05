/* 0x00291020 — FUN_00291020 (40 bytes). Runs FUN_00291468, then FUN_00291240 on the object at 0x573f68 with 7136. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_00291468(void);
extern void FUN_00291240(int obj, int size);
extern int DAT_00573f68;

void FUN_00291020(void) {
    FUN_00291468();
    FUN_00291240(DAT_00573f68, 7136);
}
