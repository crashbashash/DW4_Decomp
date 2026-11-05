/* 0x00273988 — FUN_00273988 (48 bytes). Touches the volatile word 0x004aa740, calls FUN_00275220(0) and
   returns the address of the block at 0x004aa758. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_00275220(int arg);
extern volatile int DAT_004aa740;
extern int DAT_004aa758[];

int *FUN_00273988(void) {
    DAT_004aa740;  /* volatile read, value unused */
    FUN_00275220(0);
    return DAT_004aa758;
}
