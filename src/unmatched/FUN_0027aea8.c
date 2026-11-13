extern int ps2rna_nvoice[4];
extern int ps2rna_setup_voice[4];
void FUN_0027aea8(void *arg0, int arg1) {
    if ((ps2rna_setup_voice[0] != 1) || (ps2rna_nvoice[0] > 0)) {
        *(int *)((char *)(arg0) + 92) = arg1;
    }
}
