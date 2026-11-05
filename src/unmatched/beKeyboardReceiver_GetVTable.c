struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct W { int *vt; int f[3]; };
int igObject_InitHeader(struct W *);
int igObject_Destroy(void *);
extern int DAT_0053a8b0[4];
extern char *DAT_00586dc8[4];
int beKeyboardReceiver_GetVTable(void) {
    struct W o;
    int r;
    struct Ref *p;
    igObject_InitHeader(&o);
    o.vt = DAT_0053a8b0;
    *(int *)((char *)&o + 8) = 0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0053a8b0;
    if (&*(int *)((char *)&o + 8) != 0) { p = *(struct Ref **)((char *)&o + 8); if (p != 0) { p->u.w = p->u.w - 1; if (p->u.b.cnt == 0) igObject_Destroy(p); } }
    return r;
}
