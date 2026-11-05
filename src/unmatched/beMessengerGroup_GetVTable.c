struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
int igObject_InitHeader(struct Obj *);
int FUN_00131bc0();
int ObjectRef_Destruct_001c6460();
int FUN_0033ec00();
int ObjectRef_Destruct_00150eb0();
extern int DAT_00536e40[4];
extern void * DAT_00586dc8[4];
int beMessengerGroup_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00536e40[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00536e40[0];
    FUN_0033ec00(&obj.w5, -1);
    ObjectRef_Destruct_00150eb0(&obj.w4, -1);
    ObjectRef_Destruct_001c6460(&obj.w3, -1);
    FUN_00131bc0(&obj, 0);
    return t;
}
