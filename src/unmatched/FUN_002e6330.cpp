extern "C" {
int igIGBFile_GetSectionBuffer(int *, void *, int);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int D_004fb418[4];
}
class DW4VC_108_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int); };
struct P { char pad[104]; DW4VC_108_1 *f104; };
struct Q { char pad[132]; int f132; char pad2[36]; int f172; char pad3[88]; int f264; };
extern "C" void FUN_002e6330(int *arg0, Q *arg1) {
    int sp3C;
    int *pp;
    int a;
    bool var_a0;
    int var_v1;

    igIGBFile_GetSectionBuffer(&sp3C, arg1, arg1->f132);
    pp = (int *)((int)&sp3C + 0);
    a = D_004fb418[0];
    if (*pp == DAT_004fb418[0]) {
        *arg0 = a;
        return;
    }
    arg1->f172 = arg1->f264;
    var_a0 = true;
    if (arg1->f132 != 0) {
        var_a0 = (*(DW4VC_108_1 **)((char *)arg1 + 104))->vX(arg1->f172, arg1->f132, 1) == 1;
    }
    var_v1 = DAT_004fb410[0];
    if (!(int)var_a0) {
        var_v1 = DAT_004fb418[0];
    }
    *arg0 = var_v1;
}
