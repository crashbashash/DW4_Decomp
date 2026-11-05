struct W { int *vt; int f[11]; };
int igObject_InitHeader(struct W *);
int StringChunk_ReleaseHeader();
extern int DAT_00533730[4];
extern char *DAT_00586dc8[4];
int igAdxAudio_GetVTable(void) {
    struct W o;
    int r;
    int *p; int *a1; int t;
    igObject_InitHeader(&o);
    o.vt = DAT_00533730;
    *(int *)((char *)&o + 40) = 0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_00533730;
    if (&*(int *)((char *)&o + 40) != 0) { p = *(int **)((char *)&o + 40); if (p != 0) { a1 = p - 2; t = p[-1] - 1; p[-1] = t; if (t == 0) StringChunk_ReleaseHeader(*a1, a1); } }
    return r;
}
