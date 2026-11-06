/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
union U { int vt; char b[32]; };
extern "C" {
int StringChunk_ReleaseHeader(void);
int igObject_Destroy(int *);
int igObject_InitHeader(char *);
extern int DAT_00538ce0[4];
extern int DAT_00538d40[4];
extern void * DAT_00586dc8[4];
int beSvPlatDataPC_GetVTable(void);
}
int beSvPlatDataPC_GetVTable(void) {
    union U u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[12];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00538d40[0];
    u.vt = (int)&DAT_00538ce0[0];
    s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00538d40[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return s0;
}
