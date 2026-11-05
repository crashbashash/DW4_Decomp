struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
int igObject_InitHeader(struct Obj *);
int FUN_0019c0e0();
int FUN_0019d0a0();
extern int DAT_00528e70[4];
extern void * DAT_00586dc8[4];
int igGeometry_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.vt = &DAT_00528e70[0];
    obj.w10 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00528e70[0];
    FUN_0019d0a0(&obj.w10, -1);
    FUN_0019c0e0(&obj, 0);
    return t;
}
