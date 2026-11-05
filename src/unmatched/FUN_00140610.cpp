extern "C" {
struct T { int w0; int references; char p[80]; int f88; };
struct Arg { char p[16]; int f16; int f20; int f24; int f28; int f32; char p2[4]; int f40; int f44; char p3[4]; unsigned char f52; };
int sprintf(...);
int strcpy(int a, char *b);
int strlen(char *s);
int *FUN_001405a0(int a);
T *FUN_00140c00(Arg *a, int b);
void igObject_Destroy(T *t);
extern int DAT_004d5df8[4];
extern int DAT_004d5e10[4];
extern int DAT_00587020[4];
}
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int n); };
extern "C" A *Memory_GetAllocatorBySelector(int s);
extern "C" int FUN_00140610(Arg *arg0, int arg1, A *arg2);
int FUN_00140610(Arg *arg0, int arg1, A *arg2) {
    char sp50[8204];
    T *volatile r;
    T *q;
    int *nm;
    int t;
    if (arg2 == 0) {
        arg2 = Memory_GetAllocatorBySelector(DAT_00587020[0]);
    }
    r = FUN_00140c00(arg0, 0);
    q = r;
    if (q != 0) {
        q->references = q->references + 1;
    }
    nm = &DAT_004d5df8[0];
    q = r;
    if (q != 0) {
        if (q->f88 != 0) {
            nm = FUN_001405a0(q->f88);
        }
    }
    sprintf(sp50, &DAT_004d5e10[0], nm, arg0->f16, *(volatile int *)&arg0->f20, *(volatile int *)&arg0->f24, *(volatile int *)&arg0->f28, *(volatile int *)&arg0->f32, (long long)arg0->f40, (long long)arg0->f44, (long long)arg0->f52);
    t = arg2->vX(strlen(sp50) + 1);
    strcpy(t, sp50);
    q = r;
    if (q != 0) {
        --q->references;
        if (((unsigned long long)(long long)q->references & 0x7fffffULL) == 0) {
            igObject_Destroy(q);
        }
    }
    return t;
}
