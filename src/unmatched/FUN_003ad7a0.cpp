struct P { int a; int b; };
extern "C" {
extern struct P DAT_004c91b0[];
extern int DAT_0058a810[];
int sceMcSync(int, int, int);
int FUN_00119ff0(int, int, int *, int, int);
int FUN_003ad7a0(int arg0, int arg1);
}
int FUN_003ad7a0(int arg0, int arg1) {
    int sp2C;

    sp2C = 0;
    FUN_00119ff0(DAT_004c91b0[arg1].a, DAT_004c91b0[arg1].b, &sp2C, 0, 0);
    sceMcSync(0, 0, 0);
    if (sp2C == 2) {
        DAT_0058a810[arg1] = 1;
        return 1;
    }
    DAT_0058a810[arg1] = 0;
    return 0;
}
