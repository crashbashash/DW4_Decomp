extern char DAT_004b1df0[];
int DTX_CallUrpc();
extern int ps2rna_nvoice[4];
extern int ps2rna_setup_voice[4];
void FUN_00279f68(void) {
    if (((ps2rna_setup_voice[0] != 1) || (ps2rna_nvoice[0] > 0)) && (*(int *)DAT_004b1df0 != 1)) {
        DTX_CallUrpc(0xE, 0, 0, 0, 0);
        *(int *)DAT_004b1df0 = 1;
    }
}
