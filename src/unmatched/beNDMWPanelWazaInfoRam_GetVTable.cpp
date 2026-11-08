extern "C" {
typedef struct WazaInfoRamRefHeader { char pad4[4]; int f4; } WazaInfoRamRefHeader;
int StringChunk_ReleaseHeader(void *);
int igObject_Destroy(void *);
int igObject_InitHeader(void *);
union WazaInfoRamProbe { int vt; char b[48]; };
extern int DAT_00539e90[4];
extern int DAT_0053d630[4];
extern void * DAT_00586dc8[4];
int beNDMWPanelWazaInfoRam_GetVTable(void);
}
int beNDMWPanelWazaInfoRam_GetVTable(void) {
    union WazaInfoRamProbe u;
    int temp_s1;
    WazaInfoRamRefHeader * q0;
    WazaInfoRamRefHeader * q1;

    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q0 = (WazaInfoRamRefHeader *)&u.b[40];
    *(int *)q0 = 0;
    u.vt = (int)(&DAT_0053d630[0]);
    q1 = (WazaInfoRamRefHeader *)&u.b[44];
    *(int *)q1 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)(&DAT_0053d630[0]);
    if (q1 != 0) {
        q1 = *(WazaInfoRamRefHeader **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    u.vt = (int)(&DAT_00539e90[0]);
    if (q0 != 0) {
        q0 = *(WazaInfoRamRefHeader **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s1;
}
