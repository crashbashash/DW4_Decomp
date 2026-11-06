/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; char b[48]; };
extern "C" {
int igObject_Destroy(S_ref *);
int StringChunk_ReleaseHeader(void);
int igObject_InitHeader(char *);
extern int DAT_00536680[4];
extern int DAT_00539e90[4];
extern void * DAT_00586dc8[4];
int beLayerInfoRam_GetVTable(void);
}
int beLayerInfoRam_GetVTable(void) {
    union U u;
    S_ref *q0;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00539e90[0];
    q0 = (S_ref *)&u.b[40];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00536680[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00539e90[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s0;
}
