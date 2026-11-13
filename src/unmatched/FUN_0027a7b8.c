/* Unless mode ps2rna_setup_voice is 1 with no pending count in ps2rna_nvoice, runs FUN_0027a818 and then
 * FUN_0027a8b0 on the argument. */
extern int ps2rna_setup_voice;
extern int ps2rna_nvoice;
int FUN_0027a818(int arg, int flag);
int FUN_0027a8b0(int arg, int flag);

void FUN_0027a7b8(int arg) {
    if (ps2rna_setup_voice == 1 && ps2rna_nvoice <= 0) {
        return;
    }
    FUN_0027a818(arg, 0);
    FUN_0027a8b0(arg, 0);
}
