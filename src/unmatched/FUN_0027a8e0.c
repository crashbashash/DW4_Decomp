/* Stores a word into 0x004b1df4 while the library is active (not mode 1 with no entries). */
extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;
extern int DAT_004b1df4;

void FUN_0027a8e0(int value) {
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        DAT_004b1df4 = value;
    }
}
