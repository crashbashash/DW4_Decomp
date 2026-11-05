int FUN_001a7580();
int FUN_00195a90();
int igObject_InitHeader();
extern int DAT_0052d3c0[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[96]; };
int igCollisionGroup_GetVTable(void) {
    union U u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[28] = 0;
    u.vt = (int)&DAT_0052d3c0[0];
    p = (int *)&u.b[32];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052d3c0[0];
    FUN_001a7580(p, -1);
    FUN_00195a90(u.b, 0);
    return temp_s0;
}
