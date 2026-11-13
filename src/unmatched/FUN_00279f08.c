/* Sends request 13 without payload through DTX_CallUrpc and clears the pair of words at
 * 0x004b1e00, returning the request result, unless the library is in mode 1 (0x004b1dc8) with no
 * entries (0x004b1dc0). */
struct Pair279 {
    int first;
    int second;
};

extern int DTX_CallUrpc(int request, int *payload, int words, int a3, int t0);
extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;
extern struct Pair279 DAT_004b1e00;

int FUN_00279f08(void) {
    int result;

    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        result = DTX_CallUrpc(13, 0, 0, 0, 0);
        DAT_004b1e00.first = 0;
        DAT_004b1e00.second = 0;
        /* matching construct: hand search — the request result stays live in v0 (the pair is cleared through
           v1), so it is returned on this path; the inactive path falls off the end with no value */
        return result;
    }
}
