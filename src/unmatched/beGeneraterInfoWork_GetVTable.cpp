typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; char b[48]; };
extern "C" {
int igObject_Destroy(S_ref *);
int StringChunk_ReleaseHeader(int, int *);
int igObject_InitHeader(char *);
extern int DAT_00536050[4];
extern void * DAT_00586dc8[4];
int beGeneraterInfoWork_GetVTable(void);
}
int beGeneraterInfoWork_GetVTable(void) {
    union U u;
    int t;
    char *o;
    int *a1;
    int v0;
    S_ref *p0, *p1;

    igObject_InitHeader(u.b);
    p0 = (S_ref *)&u.b[20];
    p1 = (S_ref *)&u.b[28];
    u.vt = (int)&DAT_00536050[0];
    *(int *)p0 = 0;
    *(int *)p1 = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00536050[0];
    if (p1 != 0) {
        o = *(char **)p1;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (p0 != 0) {
        p0 = *(S_ref **)p0;
        if (p0 != 0) {
            p0->f4 = (int)((int) (p0->f4 - 1));
            if (((unsigned long long) ((long long) p0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p0);
            }
        }
    }
    return t;
}
