extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;
extern int DAT_004b1df4;

int FUN_0027a910(void)
{
    if (ps2rna_setup_voice == 1 && ps2rna_nvoice <= 0)
        return 0;
    return DAT_004b1df4;
}
