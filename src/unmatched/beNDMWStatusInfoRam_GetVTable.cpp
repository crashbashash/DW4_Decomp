/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; char b[48]; };
extern "C" {
int igObject_Destroy(int *);
int igObject_InitHeader(char *);
extern int DAT_00539e90[4];
extern int DAT_0053db60[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusInfoRam_GetVTable(void);
}
int beNDMWStatusInfoRam_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p58;
    char *p5C;

    igObject_InitHeader(u.b);
    p58 = &u.b[40];
    *(int *)p58 = 0;
    u.vt = (int)&DAT_0053db60[0];
    p5C = &u.b[44];
    *(int *)p5C = 0;
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053db60[0];
    if (p5C != 0) {
        v1 = *(int **)p5C;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    u.vt = (int)&DAT_00539e90[0];
    if (p58 != 0) {
        v1 = *(int **)p58;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}
