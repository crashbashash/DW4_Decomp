union U { int vt; char b[32]; };
extern "C" {
int igObject_InitHeader(char *);
int igObject_Destroy(char *);
int StringChunk_ReleaseHeader(int, int *);
extern int DAT_00524950[4];
extern int DAT_00537af0[4];
extern void * DAT_00586dc8[4];
int beModelCtrlInfoDataSeq_GetVTable(void);
}
int beModelCtrlInfoDataSeq_GetVTable(void) {
    union U u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    int *q8;
    int *q16;

    igObject_InitHeader(u.b);
    q8 = (int *)&u.b[8];
    *q8 = 0;
    u.vt = (int)&DAT_00537af0[0];
    q16 = (int *)&u.b[16];
    *q16 = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00537af0[0];
    if (q16 != 0) {
        o = (char *)*q16;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
    if (q8 != 0) {
        temp_v1 = (int *)*q8;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return t;
}
