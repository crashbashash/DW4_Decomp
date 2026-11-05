typedef struct V3 { int a; int b; float c; } V3;
extern char DAT_00560000[];
extern V3 DAT_00486cb8;
extern V3 DAT_00486cc8;
extern int * DAT_0055ed88[4];
extern int DAT_0055f510[4];
extern int DAT_0055f518[4];
extern char GPR_00554b08;
extern unsigned char GPR_00554b0c;

void FUN_00140e90(int arg0) {
    V3 sp10;
    V3 sp0;
    int var_a1;
    int idx;
    int temp_a4;
    sp10 = DAT_00486cb8;
    temp_a4 = *(int *)((char *)(DAT_0055ed88[0]) + 92);
    idx = sp10.b;
    if (GPR_00554b0c == 0) {
        DAT_0055f510[0] = *(int *)(temp_a4 + idx);
        sp0 = DAT_00486cc8;
        DAT_0055f518[0] = *(int *)(temp_a4 + sp0.b);
        GPR_00554b0c = 1;
    }
    if (arg0 != 0) {
        var_a1 = DAT_0055f518[0];
    } else {
        var_a1 = DAT_0055f510[0];
    }
    *(int *)(temp_a4 + idx) = var_a1;
    GPR_00554b08 = arg0;
}
