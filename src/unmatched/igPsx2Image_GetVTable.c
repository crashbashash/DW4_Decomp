int StringChunk_ReleaseHeader();
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_00525630[4];
extern int DAT_00526800[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[96]; };
int igPsx2Image_GetVTable(void) {
    union U u;
    int r;
    int *v1; int *a1; int v0; int *a0;
    char *pr; char *ps;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00526800[0];
    pr = &u.b[68];
    *(int *)pr = 0;
    ps = &u.b[88];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00525630[0];
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00526800[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (pr != 0) {
        a0 = *(int **)pr;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    return r;
}
