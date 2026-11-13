extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;
extern int DAT_004b1df4;
extern int DAT_004b1df8;
extern int DAT_004b1e00[2];
extern int DAT_004b1e08;
extern char DAT_004f1810[];
int FUN_0026f4b0(const char *name, int *value);
int DTX_CallUrpc(int a0, int *a1, int a2, int *a3, int a4);

void FUN_00279e28(void)
{
    int value;
    int rate;
    int out;
    int mode;

    if (ps2rna_setup_voice == 1 && ps2rna_nvoice <= 0) {
        return;
    }
    if (FUN_0026f4b0(DAT_004f1810, &value) == 0) {
        rate = value;
    } else {
        rate = 48000;
    }
    DAT_004b1e08 = mode = DTX_CallUrpc(12, &rate, 1, &out, 1);
    DAT_004b1df4 = 0;
    DAT_004b1df8 = 0;
    if (mode == 2) {
        DAT_004b1e00[0] = 1;
        DAT_004b1e00[1] = 1;
    } else {
        DAT_004b1e00[mode] = 1;
        DAT_004b1e00[mode == 0] = 0;
    }
}
