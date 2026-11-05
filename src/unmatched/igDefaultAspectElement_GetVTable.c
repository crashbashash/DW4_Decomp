int StringChunk_ReleaseHeader();
int igObject_Destroy();
int igObject_InitHeader();
union U { int vt; int w[5]; void *p[5]; char b[20]; };
struct Rc { int vt; int rc; };
extern int DAT_00541840[4];
extern void * DAT_00586dc8[4];
int igDefaultAspectElement_GetVTable(void) {
    union U u;
    int t;
    struct Rc *a;
    int *a1;
    int v0;
    char *c;
    void **q4c;
    void **q48;
    void **q50;
    igObject_InitHeader(u.b);
    q48 = &u.p[2];
    q4c = &u.p[3];
    q50 = &u.p[4];
    u.w[0] = (int)(&DAT_00541840[0]);
    *q48 = 0;
    *q4c = 0;
    *q50 = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00541840[0]);
    if (q50 != 0) {
        a = (struct Rc *)*q50;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q4c != 0) {
        a = (struct Rc *)*q4c;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q48 != 0) {
        a = (struct Rc *)*q48;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    return t;
}
