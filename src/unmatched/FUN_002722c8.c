/* 0x002722c8 — FUN_002722c8 (56 bytes). Waits for the shared busy flag (FUN_00272228), then stores a
   sign-extended byte into the volatile control word 0x004a92cc. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_00272228(void);
extern volatile int DAT_004a92cc;

void FUN_002722c8(int value) {
    FUN_00272228();
    DAT_004a92cc = (char)value;
}
