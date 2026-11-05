typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int StringChunk_ReleaseHeader();
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_0052e010[4];
extern int DAT_0052e0a0[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[104]; };
int igElfFile_GetVTable(void) {
    union U u;
    int r;
    int *tv1, *ta1;
    int tc1;
    char *q1;
    S_ref *q2;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052e010[0];
    q1 = (char *)&u.b[8];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[12];
    *(int *)q2 = 0;
    u.vt = (int)&DAT_0052e0a0[0];
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052e010[0];
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    if (q1 != 0) {
        tv1 = *(int **)q1;
        if (tv1 != 0) {
            ta1 = tv1 - 2;
            tc1 = tv1[-1] - 1;
            tv1[-1] = tc1;
            if (tc1 == 0) {
                StringChunk_ReleaseHeader(*ta1, ta1);
            }
        }
    }
    return r;
}
