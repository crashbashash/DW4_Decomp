/* 0x002978b0 — FUN_002978b0 (92 bytes). Validates a MwsfdBufFmt value: 1, 2 and 3 pass through; anything else is reported and treated as 3. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0029a320(const char *format, ...);

extern char DAT_004f4028[]; /* "E201184 : MwsfdBufFmt value is invalid." */

int FUN_002978b0(unsigned int format) {
    int result;

    switch (format) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    default:
        FUN_0029a320(DAT_004f4028);
        result = 3;
        break;
    }
    return result;
}
