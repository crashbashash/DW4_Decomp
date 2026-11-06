typedef struct Ob { int w0; unsigned refs; int w2; } Ob;
typedef struct O { int w[6]; int f24; Ob *f28; Ob *f32; int f36; int f40; } O;
extern int DAT_00586f20[4];
void FUN_001cd150(Ob **, O *, int);
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int StringChunk_ReleaseHeader(int, int *);
void igObject_Destroy(void *);
int FUN_001c6520(O *arg0, int arg1) {
    Ob *volatile sp3C;
    Ob *a0;
    Ob *s0;
    int s0i;
    int v, old, s;
    int *hd;
    if (arg1 == 0 && arg0->f28 != 0) {
        return 1;
    }
    FUN_001cd150((Ob **)&sp3C, arg0, arg0->f24);
    if (sp3C != arg0->f28) {
        a0 = arg0->f32;
        if (a0 != 0) {
            a0->refs = a0->refs - 1;
            if ((a0->refs & 0x7fffff) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->f32 = 0;
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(16);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        s = StringPool_Intern(DAT_00586f20[0], 0);
        old = arg0->f36;
        if (old != 0) {
            hd = (int *)(old - 8);
            v = *(int *)(old - 4) - 1;
            *(int *)(old - 4) = v;
            if (v == 0) {
                StringChunk_ReleaseHeader(*hd, hd);
            }
        }
        arg0->f36 = s;
        arg0->f40 = -1;
        s0 = sp3C;
        if (s0 != 0) {
            s0->refs = s0->refs + 1;
        }
        a0 = arg0->f28;
        if (a0 != 0) {
            a0->refs = a0->refs - 1;
            if ((a0->refs & 0x7fffff) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->f28 = s0;
    }
    s0i = arg0->f28 != 0;
    a0 = sp3C;
    if (a0 != 0) {
        a0->refs = a0->refs - 1;
        if ((a0->refs & 0x7fffff) == 0) {
            igObject_Destroy(a0);
        }
    }
    return s0i;
}
