/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; int w[5]; char b[20]; };
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(S_ref *);
int igObject_InitHeader(char *);
extern int DAT_00524950[4];
extern int DAT_0053a0d0[4];
extern int DAT_0053c260[4];
extern void * DAT_00586dc8[4];
int beLightCtrl_GetVTable(void);
}
int beLightCtrl_GetVTable(void) {
    union U u;
    int temp_s1;
    char *q1;
    int *tv1, *ta1;
    int tc1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_0053a0d0[0]);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[24];
    *(int *)q2 = 0;
    u.w[0] = (int)(&DAT_0053c260[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0053a0d0[0]);
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    u.w[0] = (int)(&DAT_00524950[0]);
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
    return temp_s1;
}
