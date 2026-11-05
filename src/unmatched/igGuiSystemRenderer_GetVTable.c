struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
int igObject_InitHeader(struct Obj *);
int FUN_00197160();
int FUN_00198210();
int FUN_001d9870();
int FUN_00230f70();
int FUN_0044e0e0();
extern int DAT_00540fb0[4];
extern void * DAT_00586dc8[4];
int igGuiSystemRenderer_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00540fb0[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00540fb0[0];
    FUN_00197160(&obj.w6, -1);
    FUN_001d9870(&obj.w5, -1);
    FUN_0044e0e0(&obj.w4, -1);
    FUN_00198210(&obj.w3, -1);
    FUN_00230f70(&obj, 0);
    return t;
}
