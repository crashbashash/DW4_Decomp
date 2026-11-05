extern "C" {
int FUN_002eb010(int);
void StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int);
extern int DAT_00586f20[4];
}
struct R { int a, b, c, d; };
struct RecoveryString { void *p; ~RecoveryString() { if (p != 0) { int *t = (int *)((char *)p - 8); int v = *(int *)((char *)p - 4) - 1; *(int *)((char *)p - 4) = v; if (v == 0) StringChunk_ReleaseHeader(*t, t); } } };
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual R vf(RecoveryString *, int); };
extern "C" R FUN_00229d40(Obj *arg1, void *arg2, int arg3) {
    RecoveryString h;
    void *var_v0;
    int s = *(int *)((char *)(arg2) + 28);
    if (s == 0) { var_v0 = 0; } else {
        if (DAT_00586f20[0] == 0) {
            int v = FUN_002eb010(0x10);
            if (v != 0) { v = StringPool_Construct(v); }
            DAT_00586f20[0] = v;
        }
        var_v0 = StringPool_Intern(DAT_00586f20[0], s);
    }
    h.p = var_v0;
    return arg1->vf(&h, arg3);
}
