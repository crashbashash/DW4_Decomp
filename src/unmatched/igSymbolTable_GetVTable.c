struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; };
int FUN_002b8640();
int FUN_002b86c0();
int FUN_002b8740();
int igObject_InitHeader();
extern int DAT_0052e730[4];
extern void * DAT_00586dc8[4];
int igSymbolTable_GetVTable(void) {
    struct Obj obj;

    int temp_s3;

    igObject_InitHeader(&obj);
    obj.vt = (&DAT_0052e730[0]);
    obj.f1C = 0;
    obj.f20 = 0;
    obj.f24 = 0;
    obj.f28 = 0;
    temp_s3 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_0052e730[0]);
    FUN_002b8740(&obj.f28, -1);
    FUN_002b8740(&obj.f24, -1);
    FUN_002b86c0(&obj.f20, -1);
    FUN_002b8640(&obj.f1C, -1);
    return temp_s3;
}
