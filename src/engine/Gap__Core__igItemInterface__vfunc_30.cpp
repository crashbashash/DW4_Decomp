typedef struct Rc { int w0; int refs; } Rc;
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void vX(int **, int, int); };
extern "C" {
Rc *FUN_002279d0(int);
int FUN_0022a8d0(Rc *, int);
int FUN_0022a950(Rc *);
int FUN_0022a9b0(Rc *);
int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(Rc *);
void Gap__Core__igItemInterface__vfunc_30(O *arg0, int **arg1, int arg2, int arg3);
void Gap__Core__igItemInterface__vfunc_30(O *arg0, int **arg1, int arg2, int arg3) {
    Rc *volatile sp5C;
    int *sp58;
    volatile char sp54[4];
    int *a1;
    int v;
    int v2;
    Rc *t;
    sp54[0] = 0;
    sp5C = FUN_002279d0(0);
    FUN_0022a8d0(sp5C, arg2);
    for (;;) {
        v = FUN_0022a950(sp5C);
        if (((v != 0) ^ 1) != 0) {
            break;
        }
        sp58 = *arg1;
        if (sp58 != 0) {
            sp58[-1] = sp58[-1] + 1;
        }
        arg0->vX(&sp58, v, arg3);
        if (sp58 != 0) {
            a1 = sp58 - 2;
            v2 = sp58[-1] - 1;
            sp58[-1] = v2;
            if (v2 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        FUN_0022a9b0(sp5C);
    }
    t = sp5C;
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
}
}
