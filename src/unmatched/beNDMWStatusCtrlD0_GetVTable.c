struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; int f30; int f34; int f38; int f3C; int f40; int f44; int f48; int f4C; int f50; int f54; int f58; int f5C; int f60; int f64; int f68; int f6C; int f70; int f74; int f78; int f7C; };
int FUN_00226990();
int FUN_003b6770();
int ObjectRef_Destruct_00150eb0();
int igObject_InitHeader();
extern int DAT_0053eed0[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusCtrlD0_GetVTable(void) {
    struct Obj obj;

    int temp_s1;

    igObject_InitHeader(&obj);
    obj.f34 = 0;
    obj.f38 = 0;
    obj.f3C = 0;
    obj.f40 = 0;
    obj.f44 = 0;
    obj.f48 = 0;
    obj.f4C = 0;
    obj.vt = (&DAT_0053eed0[0]);
    obj.f64 = 0;
    obj.f70 = 0;
    temp_s1 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_0053eed0[0]);
    FUN_00226990(&obj.f70, -1);
    ObjectRef_Destruct_00150eb0(&obj.f64, -1);
    FUN_003b6770(&obj, 0);
    return temp_s1;
}
