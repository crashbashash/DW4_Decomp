/* 0x0027aa08 — FUN_0027aa08 (52 bytes). Reports a fixed output format while the library is active (not mode 1
   with no entries): 0 into *first and 48000 (0xBB80, a sample rate) into *rate. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int DAT_004b1dc0;
extern int DAT_004b1dc8;

void FUN_0027aa08(int unused, int *first, int *rate) {
    if (DAT_004b1dc8 != 1 || DAT_004b1dc0 > 0) {
        *first = 0;
        *rate = 48000;
    }
}
