/* 0x00272300 — FUN_00272300 (56 bytes). Waits for the shared busy flag (FUN_00272228), then stores a
   sign-extended byte into the volatile control word 0x004a92d0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_00272228(void);
extern volatile int DAT_004a92d0;

void FUN_00272300(int value) {
    FUN_00272228();
    DAT_004a92d0 = (char)value;
}
