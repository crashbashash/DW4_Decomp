int StringChunk_ReleaseHeader();
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_00541fe0[4];
extern int DAT_00540e30[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[16]; };
int igActorManagerParams_GetVTable(void) {
    union U u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00540e30[0];
    u.vt = (int)&DAT_00541fe0[0];
    s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00540e30[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return s0;
}
