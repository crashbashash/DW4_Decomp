extern "C" {
struct P { unsigned short f0; unsigned short f2; unsigned short f4; char p6[2]; int *f8; short *f12; int f16; };
int FUN_00165d10(void *a);
int FUN_002eb010(int n);
P *Memory_AllocateBufferDirect(int n, int a);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(int p);
int *StringPool_Intern(int pool, int *s);
int thunk_FUN_003065f0(int a, int b, int *c, int *d, int e, int f);
extern int DAT_004df350[4];
extern void * DAT_00586dc8[4];
extern int DAT_00586f20[4];
}
class Buf { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void b53(); virtual short *vB(int n, int sz); virtual int vA(int n, int sz, int al); };
extern "C" Buf *Memory_FindBufferOwner(P *p);
struct Arg { char pad[868]; P *f868; int f872; };
extern "C" void FUN_001690d0(Arg *arg0);
void FUN_001690d0(Arg *arg0) {
    int sp5C;
    int i;
    P *p;
    int n;
    int v;
    int *old;
    int *s3;
    Buf *b;
    sp5C = 4;
    thunk_FUN_003065f0(*(int *)((char *)(DAT_00586dc8[0]) + 56), 4, &DAT_004df350[0], &sp5C, 4, 0);
    p = Memory_AllocateBufferDirect(20, FUN_00165d10(arg0));
    if (p != 0) {
        n = sp5C;
        p->f8 = 0;
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(16);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        s3 = StringPool_Intern(DAT_00586f20[0], &DAT_004df350[0]);
        old = p->f8;
        if (old != 0) {
            int *a1 = old - 2;
            int v0 = old[-1] - 1;
            old[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        p->f8 = s3;
        if (n == 0) {
            n = 1;
        }
        b = Memory_FindBufferOwner(p);
        p->f16 = b->vA(n, 48, 16);
        p->f12 = b->vB(n, 2);
        i = 0;
        p->f2 = n;
        p->f0 = n;
        p->f4 = n;
        while (i < n) {
            p->f12[i] = i;
            i = i + 1;
        }
    }
    arg0->f868 = p;
    arg0->f872 = -1;
}
