/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; char b[56]; };
extern "C" {
int StringChunk_ReleaseHeader(void);
int igObject_Destroy(S_ref *);
int igObject_InitHeader(char *);
extern int DAT_0053bf20[4];
extern int DAT_0053c070[4];
extern void * DAT_00586dc8[4];
int beSvFormatApi_GetVTable(void);
}
int beSvFormatApi_GetVTable(void) {
    union U u;
    int r;
    int *tv1, *ta1;
    int tc1;
    S_ref *q2;
    S_ref *q1;
    S_ref *q3;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053c070[0];
    q1 = (S_ref *)&u.b[48];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[52];
    *(int *)q2 = 0;
    q3 = (S_ref *)&u.b[56];
    *(int *)q3 = 0;
    u.vt = (int)&DAT_0053bf20[0];
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053c070[0];
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q3);
            }
        }
    }
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
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return r;
}
