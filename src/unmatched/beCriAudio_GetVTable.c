int StringChunk_ReleaseHeader();
int igObject_Destroy();
int igObject_InitHeader();
union U { int vt; int w[8]; void *p[8]; char b[32]; };
struct Rc { int vt; int rc; };
extern int DAT_00534e30[4];
extern void * DAT_00586dc8[4];
int beCriAudio_GetVTable(void) {
    union U u;
    int t;
    struct Rc *a;
    int *a1;
    int v0;
    char *c;
    void **q38;
    void **q3c;
    igObject_InitHeader(u.b);
    q38 = &u.p[2];
    q3c = &u.p[3];
    u.w[0] = (int)(&DAT_00534e30[0]);
    *q38 = 0;
    *q3c = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00534e30[0]);
    if (q3c != 0) {
        a = (struct Rc *)*q3c;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q38 != 0) {
        a = (struct Rc *)*q38;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    return t;
}
