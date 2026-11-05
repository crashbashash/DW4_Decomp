/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; int w[5]; char b[20]; };
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_InitHeader(char *);
extern int DAT_00524950[4];
extern int DAT_005392f0[4];
extern void * DAT_00586dc8[4];
int beSoundData_GetVTable(void);
}
int beSoundData_GetVTable(void) {
    union U u;
    int temp_s0;
    char *q1;
    int *tv1, *ta1;
    int tc1;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00524950[0]);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_005392f0[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
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
    return temp_s0;
}
