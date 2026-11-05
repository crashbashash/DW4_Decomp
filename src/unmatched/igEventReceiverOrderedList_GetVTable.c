int FUN_00451160();
int igObject_InitHeader();
extern int DAT_00541910[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[32]; };
int igEventReceiverOrderedList_GetVTable(void) {
    union U u;
    int t;
    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[20] = 0;
    u.vt = (int)&DAT_00541910[0];
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00541910[0];
    FUN_00451160(u.b, 0);
    return t;
}
