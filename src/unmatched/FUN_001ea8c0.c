int strlen();
int FUN_001eafa0();
int FUN_00202300();
int FUN_0020d790();
int FUN_0020d820();
extern int DAT_00467180[4];
extern char DAT_0048dd60[16];
extern int DAT_00562d90[4];
extern int DAT_00562d94[4];
extern int DAT_00562d98[4];
extern int DAT_00562d9c[4];
extern char DAT_00562da0[16];
extern int DAT_00568da0[4];
void FUN_001ea8c0(int arg0, int arg1) {
    int i;
    int len;
    DAT_00562d90[0] = 0;
    DAT_00562d94[0] = 0;
    DAT_00562d98[0] = 0x200;
    DAT_00562d9c[0] = 0x800;
    for (i = 0; i < 0x180; i++) {
        *(int *)(DAT_00562da0 + (i << 6) + 8) = -1;
    }
    DAT_00568da0[0] = -1;
    len = strlen(DAT_0048dd60);
    for (i = 0; i < len; i++) {
        if (DAT_0048dd60[i] == '.') {
            DAT_0048dd60[i] = '\n';
        }
    }
    if (arg0 != 0 && FUN_0020d790(arg1, DAT_00467180) != 0) {
        FUN_001eafa0(arg0);
        FUN_0020d820();
        FUN_00202300();
    }
}
