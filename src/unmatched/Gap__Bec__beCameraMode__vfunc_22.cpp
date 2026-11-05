class C;
extern "C" {
int FUN_004650a0();
int FUN_004650d0(void *);
int FUN_004651e0(void *);
extern int DAT_0058cd38[4];
extern int DAT_0058cd60[4];
extern int DAT_0058cd68[4];
extern int DAT_0058cd70[4];
void Gap__Bec__beCameraMode__vfunc_22(C *, int *);
}
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void v124(); virtual void v128(); };
void Gap__Bec__beCameraMode__vfunc_22(C *arg0, int *arg1) {
    int t = arg1[2];
    int k;
    if (t == DAT_0058cd38[0]) { FUN_004650a0(); FUN_004650d0(arg0); return; }
    if (t == DAT_0058cd60[0] || t == DAT_0058cd68[0] || t == DAT_0058cd70[0]) { FUN_004651e0(arg0); return; }
    k = arg1[0];
    if (k == 0) { FUN_004650a0(); FUN_004650d0(arg0); arg0->v124(); }
    else if (k == 1) { arg0->v128(); }
}
