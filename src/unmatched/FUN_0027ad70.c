int ADXMSG_PrintErr();
extern int ps2rna_nvoice[4];
extern int ps2rna_setup_voice[4];
extern int DAT_004f1908[4];
void FUN_0027ad70(void) {
    if ((ps2rna_setup_voice[0] != 1) || (ps2rna_nvoice[0] > 0)) {
        ADXMSG_PrintErr(&DAT_004f1908[0]);
    }
}
