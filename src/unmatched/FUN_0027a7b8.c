/* 0x0027a7b8 — FUN_0027a7b8 (92 bytes). Unless mode DAT_004b1dc8 is 1 with no pending count in DAT_004b1dc0, runs FUN_0027a818 and then FUN_0027a8b0 on the argument. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int DAT_004b1dc8;
extern int DAT_004b1dc0;
int FUN_0027a818(int arg, int flag);
int FUN_0027a8b0(int arg, int flag);

void FUN_0027a7b8(int arg) {
    if (DAT_004b1dc8 == 1 && DAT_004b1dc0 <= 0) {
        return;
    }
    FUN_0027a818(arg, 0);
    FUN_0027a8b0(arg, 0);
}
