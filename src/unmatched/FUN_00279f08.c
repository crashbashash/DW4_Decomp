/* 0x00279f08 — FUN_00279f08 (92 bytes). Sends request 13 without payload through FUN_00273820 and clears
   the pair of words at 0x004b1e00, returning the request result, unless the library is in mode 1 (0x004b1dc8) with no entries (0x004b1dc0).
   Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Pair279 {
    int first;
    int second;
};

extern int FUN_00273820(int request, int *payload, int words, int a3, int t0);
extern int DAT_004b1dc0;
extern int DAT_004b1dc8;
extern struct Pair279 DAT_004b1e00;

int FUN_00279f08(void) {
    int result;

    if (DAT_004b1dc8 != 1 || DAT_004b1dc0 > 0) {
        result = FUN_00273820(13, 0, 0, 0, 0);
        DAT_004b1e00.first = 0;
        DAT_004b1e00.second = 0;
        /* matching construct: hand search — the request result stays live in v0 (the pair is cleared through
           v1), so it is returned on this path; the inactive path falls off the end with no value */
        return result;
    }
}
