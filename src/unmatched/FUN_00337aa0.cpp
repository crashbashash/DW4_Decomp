extern "C" {
int FUN_0016cdd0(int, int, int, int);
int FUN_0016cde0(int);
int FUN_00308320(int[4]);
int FUN_003378e0(int, int, int, int, int, int, int);
extern int DAT_00500d70[4];
extern int DAT_005878b8[4];
extern int DAT_005878c0[4];
extern int DAT_005878d8[4];
extern unsigned char GPR_00554e00;
struct S { char p[32]; int f32; int f36; };
int FUN_00337aa0(struct S *arg0, int arg1) {
    int s2;
    int s1;
    int s0;
    int v0;
    s2 = FUN_0016cde0(DAT_005878d8[0]);
    s1 = arg0->f32;
    s0 = arg0->f36;
    if (DAT_005878c0[0] == 0 && GPR_00554e00 == 0) {
        v0 = FUN_00308320(DAT_00500d70);
        if (v0 != 1 && v0 == 2) {
            GPR_00554e00 = 1;
        }
    }
    DAT_005878b8[0] = FUN_003378e0(DAT_005878c0[0], arg1, 0, (s2 != 0) ? 448 : 0, s1, s0, 1);
    FUN_0016cdd0(DAT_005878d8[0], DAT_005878c0[0], DAT_005878b8[0], 1);
    return 1;
}
}
