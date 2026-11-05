/* 0x0027a8e0 — FUN_0027a8e0 (48 bytes). Stores a word into 0x004b1df4 while the library is active (not
   mode 1 with no entries). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int DAT_004b1dc0;
extern int DAT_004b1dc8;
extern int DAT_004b1df4;

void FUN_0027a8e0(int value) {
    if (DAT_004b1dc8 != 1 || DAT_004b1dc0 > 0) {
        DAT_004b1df4 = value;
    }
}
