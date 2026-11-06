/* Selects the timer channel (-1, 0 or 1) as global stream parameter 61 through FUN_002ad950,
 * reporting any other value. */
extern void FUN_0029a320(const char *msg);
extern void FUN_002ad950(int stream, int param, int value);
extern char DAT_004f3ff8[]; /* "E309101 : Timer channel is only -1, 0, 1." */

void FUN_00297718(int ch) {
    if (ch < -1 || ch > 1) {
        FUN_0029a320(DAT_004f3ff8);
        return;
    }
    FUN_002ad950(0, 61, ch);
}
