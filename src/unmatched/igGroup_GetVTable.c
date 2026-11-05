struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
int FUN_001958f0();
int FUN_00195970();
int igObject_InitHeader();
extern int DAT_00528dd0[4];
extern void * DAT_00586dc8[4];
int igGroup_GetVTable(void) {
    struct Obj obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.fC = 0;
    obj.f10 = 0;
    obj.vt = (&DAT_00528dd0[0]);
    obj.f1C = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_00528dd0[0]);
    FUN_001958f0(&obj.f1C, -1);
    FUN_00195970(&obj, 0);
    return temp_s0;
}
