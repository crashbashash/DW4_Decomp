int StringChunk_ReleaseHeader();
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_00524950[4];
extern int DAT_005286a0[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[32]; };
int igSkeleton_GetVTable(void) {
    union U u;
    int temp_s1;
    int *ps;
    int *pr;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = (int *)&u.b[8];
    *ps = 0;
    u.vt = (int)&DAT_005286a0[0];
    pr = (int *)&u.b[16];
    *pr = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_005286a0[0];
    if (pr != 0) {
        o = (char *)*pr;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
    if (ps != 0) {
        temp_v1 = (int *)*ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}
