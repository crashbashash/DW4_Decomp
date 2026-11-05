/* 0x00291af8 — FUN_00291af8 (80 bytes). Maps a creation-parameter buffer format to the internal one (1 -> 1, 0/2 -> 2, 3 -> 3); anything else reports "MwsfdCrePrm: illigal buffmt." through FUN_0029a320 and yields 3. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0029a320(const char *message);

extern char DAT_004f2b28[]; /* "E206011: MwsfdCrePrm: illigal buffmt." */

int FUN_00291af8(int format) {
    int result;

    if (format == 1) {
        result = 1;
    } else if (format == 0) {
        result = 2;
    } else if (format == 2) {
        result = 2;
    } else if (format == 3) {
        result = 3;
    } else {
        FUN_0029a320(DAT_004f2b28);
        result = 3;
    }
    return result;
}
