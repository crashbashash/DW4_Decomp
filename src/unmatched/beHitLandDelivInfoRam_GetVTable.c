typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int igObject_Destroy();
int StringChunk_ReleaseHeader();
int igObject_InitHeader();
extern int DAT_00536230[4];
extern int DAT_00539e90[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[112]; };
int beHitLandDelivInfoRam_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;

    igObject_InitHeader(u.b);
    q1 = (S_ref *)&u.b[40];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00536230[0];
    q0 = (S_ref *)&u.b[44];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00536230[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&DAT_00539e90[0];
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}
