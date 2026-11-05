int igObject_InitHeader();
int FUN_00196a50();
int FUN_00195a90();
extern int DAT_00528590[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[48]; };
int igSwitch_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[28] = 0;
    u.vt = (int)&DAT_00528590[0];
    ps = &u.b[32];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00528590[0];
    FUN_00196a50(ps, -1);
    FUN_00195a90(u.b, 0);
    return temp_s0;
}
