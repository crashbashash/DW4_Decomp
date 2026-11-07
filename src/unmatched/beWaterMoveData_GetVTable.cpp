union U { int vt; char b[32]; };
extern "C" {
int igObject_Destroy(int *);
int igObject_InitHeader(char *);
extern int DAT_00539940[4];
extern int DAT_00539940[4];
extern void * DAT_00586dc8[4];
int beWaterMoveData_GetVTable(void);
}
int beWaterMoveData_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *p;
    int v;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00539940[0];
    ps = &u.b[20];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00539940[0];
    if (ps != 0) {
        p = *(int **)ps;
        if (p != 0) {
            v = p[1] - 1;
            p[1] = v;
            if ((p[1] & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}
