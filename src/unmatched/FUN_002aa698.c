/* 0x002aa698 — FUN_002aa698 (36 bytes). Runs FUN_002aa6c0 and clears DAT_004beb24. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_002aa6c0(void);
extern int DAT_004beb24;

void FUN_002aa698(void) {
    FUN_002aa6c0();
    DAT_004beb24 = 0;
}
