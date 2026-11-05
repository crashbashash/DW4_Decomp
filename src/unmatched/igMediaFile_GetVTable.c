int igObject_InitHeader();
int FUN_002c13b0();
int FUN_002c0790();
extern int DAT_0052f9a0[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[80]; };
int igMediaFile_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[40] = 0;
    u.vt = (int)&DAT_0052f9a0[0];
    ps = &u.b[64];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052f9a0[0];
    FUN_002c13b0(ps, -1);
    FUN_002c0790(u.b, 0);
    return temp_s0;
}
