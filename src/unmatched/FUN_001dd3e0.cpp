extern "C" {
int igMatrix44f_SetIdentity(...);
int FUN_001904f0(...);
extern float DAT_004e1058[4];
extern float DAT_004e105c[4];
extern float DAT_004e1060[4];
void FUN_001dd3e0(void *arg0, int arg1);
}
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void vSet(int, int *); virtual void vGet(int, int *); virtual void e0(); virtual void e1(); virtual void e2(); virtual int vCount(); };
struct F { char p[44]; float a; float b; float c; };
void FUN_001dd3e0(void *arg0, int arg1) {
    int sp50[16];
    int i;
    int n;
    n = ((V *)arg0)->vCount();
    for (i = 0; i < n; i++) {
        igMatrix44f_SetIdentity(sp50);
        ((V *)arg0)->vGet(i, sp50);
        FUN_001904f0(sp50, sp50, arg1);
        ((V *)arg0)->vSet(i, sp50);
        ((F *)arg0)->a = DAT_004e1058[0];
        ((F *)arg0)->b = DAT_004e105c[0];
        ((F *)arg0)->c = DAT_004e1060[0];
    }
}
