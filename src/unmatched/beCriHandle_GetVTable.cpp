union U { int vt; char b[48]; };
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(int *);
int igObject_InitHeader(char *);
extern int DAT_00524950[4];
extern int DAT_00534f60[4];
extern void * DAT_00586dc8[4];
int beCriHandle_GetVTable(void);
}
int beCriHandle_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p4C;
    char *p48;
    char *p50;

    igObject_InitHeader(u.b);
    p48 = &u.b[8];
    *(int *)p48 = 0;
    u.vt = (int)&DAT_00534f60[0];
    p4C = &u.b[12];
    *(int *)p4C = 0;
    p50 = &u.b[16];
    *(int *)p50 = 0;
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00534f60[0];
    if (p50 != 0) {
        v1 = *(int **)p50;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p4C != 0) {
        v1 = *(int **)p4C;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
    if (p48 != 0) {
        v1 = *(int **)p48;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return r;
}
