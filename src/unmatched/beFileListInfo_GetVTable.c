int FUN_00131b20();
int FUN_00199450();
int StringRef_Destruct_00130720();
int igObject_InitHeader();
extern int DAT_00535870[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[32]; };
int beFileListInfo_GetVTable(void) {
    union U u;
    int temp_s1;
    char *p2;
    char *p1;
    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&DAT_00535870[0];
    p2 = &u.b[20];
    *(int *)p2 = 0;
    p1 = &u.b[24];
    *(int *)p1 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00535870[0];
    FUN_00199450(p1, -1);
    StringRef_Destruct_00130720(p2, -1);
    FUN_00131b20(u.b, 0);
    return temp_s1;
}
