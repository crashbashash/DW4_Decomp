/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct W { int *vt; int f[7]; };
extern "C" {
int igObject_InitHeader(struct W *);
int StringChunk_ReleaseHeader(int, int *);
extern int DAT_0053cc00[4];
extern char *DAT_00586dc8[4];
int beNDMWMcSlotXbox_GetVTable(void);
}
int beNDMWMcSlotXbox_GetVTable(void) {
    struct W o;
    int r;

    int *p; int *a1; int t;
    igObject_InitHeader(&o);
    o.vt = DAT_0053cc00;
    *(int *)((char *)&o + 24) = 0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0053cc00;
    if (&*(int *)((char *)&o + 24) != 0) { p = *(int **)((char *)&o + 24); if (p != 0) { a1 = p - 2; t = p[-1] - 1; p[-1] = t; if (t == 0) StringChunk_ReleaseHeader(*a1, a1); } }
    return r;
}
