int StringChunk_ReleaseHeader();
int igObject_Destroy();
int igObject_InitHeader();
union U { int vt; int w[8]; void *p[8]; char b[32]; };
struct Rc { int vt; int rc; };
extern int DAT_00524950[4];
extern int DAT_0052d660[4];
extern void * DAT_00586dc8[4];
int igLuaState_GetVTable(void) {
    union U u;
    int t;
    struct Rc *a;
    int *a1;
    int v0;
    char *c;
    void **q38;
    void **q40;
    igObject_InitHeader(u.b);
    q38 = &u.p[2];
    *q38 = 0;
    u.w[0] = (int)(&DAT_0052d660[0]);
    q40 = &u.p[4];
    *q40 = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052d660[0]);
    if (q40 != 0) {
        a = (struct Rc *)*q40;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    u.w[0] = (int)(&DAT_00524950[0]);
    if (q38 != 0) {
        c = (char *)*q38;
        if (c != 0) {
            a1 = (int *)(c - 8);
            v0 = *(int *)(c - 4) - 1;
            *(int *)(c - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}
