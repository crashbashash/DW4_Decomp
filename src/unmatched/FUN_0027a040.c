extern int ps2rna_setup_voice;
extern int ps2rna_nvoice;
extern int DAT_004b1df0;
void FUN_0027a040(void *handle, int value) {
    if (ps2rna_setup_voice == 1 && ps2rna_nvoice <= 0) {
        return;
    }
    if (*(signed char *)((char *)handle + 84) == value) {
        return;
    }
    if (DAT_004b1df0 == 0 && value == 1) {
        return;
    }
    *(signed char *)((char *)handle + 84) = value;
}
