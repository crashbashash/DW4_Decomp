struct Obj { int *vt; int w[15]; };
int FUN_001489a0();
int FUN_00150180();
int FUN_0019eeb0();
int FUN_001a0790();
int FUN_00227e70();
int igObject_InitHeader(struct Obj *);
extern int DAT_00530630[4];
extern void * DAT_00586dc8[4];
int igDriverDatabase_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00530630[0];
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.w[7] = 0;
    obj.w[8] = 0;
    obj.w[9] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00530630[0];
    FUN_001489a0(&obj.w[9], -1);
    FUN_001489a0(&obj.w[8], -1);
    FUN_00150180(&obj.w[7], -1);
    FUN_0019eeb0(&obj.w[4], -1);
    FUN_00227e70(&obj.w[3], -1);
    FUN_00227e70(&obj.w[2], -1);
    FUN_001a0790(&obj.w[1], -1);
    return r;
}
