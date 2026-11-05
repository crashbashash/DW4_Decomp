int FUN_00130720();
int FUN_0014f4e0();
int igObject_InitHeader();
extern int DAT_00530200[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[48]; };
int igExternalInfoEntry_GetVTable(void) {
    union U u;
    int temp_s0;
    int *p;
    int *q;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&DAT_00530200[0];
    p = (int *)&u.b[28];
    q = (int *)&u.b[36];
    *p = 0;
    *q = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00530200[0];
    FUN_00130720(q, -1);
    FUN_00130720(p, -1);
    FUN_0014f4e0(u.b, 0);
    return temp_s0;
}
