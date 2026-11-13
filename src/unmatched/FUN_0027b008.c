extern int ps2rna_setup_voice;
extern int ps2rna_nvoice;
int FUN_0027b008(void *arg0) {
    if (ps2rna_setup_voice == 1 && ps2rna_nvoice <= 0) {
        return 0;
    }
    return *(int *)((char *)arg0 + 92);
}
