void ADXMSG_PrintErr(const char *format, ...);
extern char DAT_004f1540[];
extern char DAT_004f1570[];
extern char DAT_004f15a0[];
extern int DAT_004b1de8;
extern int DAT_004b1dec;
extern int ps2rna_iop_wksize;
extern int ps2rna_setup_voice;
extern int ps2rna_nvoice;

void FUN_00279218(int nste, int nmono)
{
    int n;

    if (nste < 0) {
        ADXMSG_PrintErr(DAT_004f1540, nste);
        return;
    }
    if (nmono < 0) {
        ADXMSG_PrintErr(DAT_004f1570, nmono);
        return;
    }
    n = nste * 2 + nmono;
    if (n > 32) {
        ADXMSG_PrintErr(DAT_004f15a0, 32);
        return;
    }
    ps2rna_nvoice = n;
    DAT_004b1de8 = nste;
    DAT_004b1dec = nmono;
    ps2rna_iop_wksize = n * 0x4100;
    ps2rna_setup_voice = 1;
}
