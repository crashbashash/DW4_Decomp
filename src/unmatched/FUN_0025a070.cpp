extern "C" {
int FUN_00463560(void *, void *);
void *FUN_002c43b0(int);
int FUN_002eb010(int);
void *FUN_0045a680(int);
int FUN_0025ac60(void *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, void *);
extern int DAT_004ecf58[4];
extern int DAT_00586f20[4];
}
struct R { int w0; int refs; int f8; };
extern "C" void igObject_Destroy(R *);
struct Ref { R *p; Ref() {} };
extern "C" Ref FUN_002364e0(int);
struct S {
    char p0[28]; R *f28; R *f32; R *f36; R *f40; char f44; R *f48; R *f52; void *f56;
};
#define RETAIN(x) { R *t_ = (x); if (t_ != 0) t_->refs = t_->refs + 1; }
extern "C" S *FUN_0025a070(S *arg0);
S *FUN_0025a070(S *arg0) {
    int s2;
    R *s1;
    int v;
    {
        Ref r = FUN_002364e0(0);
        FUN_00463560(arg0, r.p);
        if (r.p != 0) {
            r.p->refs = r.p->refs - 1;
            if (((unsigned long long)(long long)r.p->refs & 0x7fffffULL) == 0) igObject_Destroy(r.p);
        }
    }
    volatile char sp48[4];
    volatile char sp44[4];
    arg0->f28 = 0; RETAIN(arg0->f28)
    arg0->f32 = 0; RETAIN(arg0->f32)
    arg0->f36 = 0; RETAIN(arg0->f36)
    arg0->f40 = 0; RETAIN(arg0->f40)
    arg0->f44 = 0;
    arg0->f48 = 0; RETAIN(arg0->f48)
    sp48[0] = 0;
    arg0->f52 = (R *)FUN_002c43b0(0);
    sp44[0] = 0;
    arg0->f56 = FUN_0045a680(0);
    s1 = arg0->f52;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    s2 = StringPool_Intern(DAT_00586f20[0], &DAT_004ecf58[0]);
    {
        int *old = (int *)s1->f8;
        if (old != 0) {
            int *hdr = old - 2;
            int r = old[-1] - 1;
            old[-1] = r;
            if (r == 0) {
                StringChunk_ReleaseHeader(*hdr, hdr);
            }
        }
    }
    s1->f8 = s2;
    FUN_0025ac60(arg0);
    return arg0;
}
