int FUN_002ba970();
int FUN_002cf040();
int igObject_InitHeader();
extern int DAT_0052ddf0[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[48]; };
int igStandardQueue_GetVTable(void) {
    union U u;
    int temp_s2;
    char *p2;
    char *p1;
    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&DAT_0052ddf0[0];
    p1 = &u.b[12];
    *(int *)p1 = 0;
    p2 = &u.b[16];
    *(int *)p2 = 0;
    *(int *)&u.b[20] = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052ddf0[0];
    FUN_002ba970(&u.b[20], -1);
    FUN_002ba970(p2, -1);
    FUN_002ba970(p1, -1);
    FUN_002cf040(u.b, 0);
    return temp_s2;
}
