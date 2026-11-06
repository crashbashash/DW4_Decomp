typedef struct Ob { int w0; unsigned refs; int w2; } Ob;
typedef struct Hd { int w[5]; int f20; int w6[2]; Ob *f32; } Hd;
typedef struct Pn { Hd h; } Pn;
typedef struct O { int w[3]; Hd *f12; } O;
typedef struct Gl { int w[2]; int f8; } Gl;
extern int DAT_00586f20[4];
extern Gl *DAT_004854a0[4];
extern char DAT_004fb390[];
int FUN_00124e10(int);
Ob *FUN_002c72c0(int);
int FUN_00301000(void);
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, char *);
int StringChunk_ReleaseHeader(int, int *);
void igObject_Destroy(void *);
int FUN_00308850(O *, Hd *);
Hd *FUN_00308a90(O *arg0) {
    Ob *volatile sp4C;
    Ob *t;
    Ob *a0;
    Hd *s0;
    int s2;
    int old;
    int v;
    int *hd;
    if (arg0->f12 == 0) {
        sp4C = FUN_002c72c0(FUN_00301000());
        t = sp4C;
        if (t != 0) {
            t->refs = t->refs + 1;
        }
        a0 = (Ob *)arg0->f12;
        if (a0 != 0) {
            a0->refs = a0->refs - 1;
            if ((a0->refs & 0x7fffff) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->f12 = (Hd *)t;
        t = sp4C;
        if (t != 0) {
            t->refs = t->refs - 1;
            a0 = sp4C;
            if ((a0->refs & 0x7fffff) == 0) {
                igObject_Destroy(a0);
            }
        }
        s0 = arg0->f12;
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(16);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        s2 = StringPool_Intern(DAT_00586f20[0], DAT_004fb390);
        old = s0->f20;
        if (old != 0) {
            hd = (int *)(old - 8);
            v = *(int *)(old - 4) - 1;
            *(int *)(old - 4) = v;
            if (v == 0) {
                StringChunk_ReleaseHeader(*hd, hd);
            }
        }
        s0->f20 = s2;
        arg0->f12->f32 = (Ob *)arg0;
        FUN_00308850(arg0, arg0->f12);
    }
    FUN_00124e10(DAT_004854a0[0]->f8);
    return arg0->f12;
}
