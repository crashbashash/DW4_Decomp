struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; };
int igObject_InitHeader(struct Obj *);
int FUN_001d3650();
int FUN_00130720();
int FUN_00344030();
extern int DAT_00538040[4];
extern void * DAT_00586dc8[4];
int beMovieInfoData_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00538040[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00538040[0];
    FUN_001d3650(&obj.w6, -1);
    FUN_00130720(&obj.w5, -1);
    FUN_00130720(&obj.w4, -1);
    FUN_00344030(&obj, 0);
    return t;
}
