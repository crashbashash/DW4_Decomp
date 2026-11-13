/* Reports a fixed output format while the library is active (not mode 1 with no entries): 0 into
 * *first and 48000 (0xBB80, a sample rate) into *rate. */
extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;

void FUN_0027aa08(int unused, int *first, int *rate) {
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        *first = 0;
        *rate = 48000;
    }
}
