extern "C" {
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int StringChunk_ReleaseHeader(int, int *);
int FUN_00308390(int *, int, int);
int FUN_002d7da0(void *, int, int);
extern int DAT_00586f20[4];
extern int DAT_004f99f0[4];
extern unsigned char GPR_00554c00;
}
struct A { char pad[200]; int f200; };
struct B { char pad[160]; int f160; };
class O { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40();
 virtual void v172(int);
 char p1[8]; int f12; char p2[8]; int f24; char p3[4]; int f32; char p4[4]; int f40;
};
extern "C" void FUN_002e25a0(O *arg0, void *arg1);
void FUN_002e25a0(O *arg0, void *arg1) {
    int s2, v, old, r;
    int *hd;
    s2 = ((A *)arg1)->f200;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    s2 = StringPool_Intern(DAT_00586f20[0], s2);
    old = arg0->f40;
    if (old != 0) {
        hd = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    arg0->f40 = s2;
    arg0->v172(((B *)arg1)->f160);
    if (arg0->f24 == 0 && GPR_00554c00 == 0) {
        r = FUN_00308390(&DAT_004f99f0[0], arg0->f32, arg0->f40);
        if (r != 1 && r == 2) {
            GPR_00554c00 = 1;
        }
    }
    FUN_002d7da0(arg1, arg0->f12, arg0->f24);
}
