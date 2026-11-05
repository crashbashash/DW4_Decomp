/* 0x00297b88 — FUN_00297b88 (76 bytes). Validates a chroma position: 0 and 1 pass through; anything else is reported and gives 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0029a320(const char *format, ...);

extern char DAT_004f40a0[]; /* "E301274 : chromapos is invalid." */

int FUN_00297b88(int position) {
    int result = 1;

    switch (position) {
    case 0:
        result = 0;
        break;
    case 1:
        result = 1;
        break;
    default:
        FUN_0029a320(DAT_004f40a0);
        break;
    }
    return result;
}
