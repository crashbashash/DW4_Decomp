struct T { int w; int references; };
struct F { int *vt; char pad[4]; int *str; char pad2[12]; struct T *ref; char pad3[20]; };
extern "C" {
void StringChunk_ReleaseHeader(int, int *);
void igObject_Destroy(struct T *);
int igObject_InitHeader(struct F *);
extern int DAT_0053dea0[4];
extern int DAT_0053a0d0[4];
extern int DAT_00524950[4];
extern char *DAT_00586dc8[4];
int beNDMWStageCtl_GetVTable(void);
}
int beNDMWStageCtl_GetVTable(void) {
    struct F o;
    int r;
    int *s;
    int *h;
    int c;
    struct T *a;

    igObject_InitHeader(&o);
    o.vt = DAT_0053a0d0;
    o.str = 0;
    o.ref = 0;
    o.vt = DAT_0053dea0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0053a0d0;
    if (&o.ref != 0) {
        a = o.ref;
        if (a != 0) {
            a->references = a->references - 1;
            if ((((unsigned long long)((long long)a->references << 0x29)) >> 0x29) == 0) igObject_Destroy(a);
        }
    }
    o.vt = DAT_00524950;
    if (&o.str != 0) {
        s = o.str;
        if (s != 0) {
            h = s - 2;
            c = s[-1] - 1;
            s[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*h, h);
        }
    }
    return r;
}
