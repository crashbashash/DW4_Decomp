typedef struct { int *vt; int pad[7]; } Obj;
int igObject_InitHeader();
extern int DAT_00527a90[4];
extern void * DAT_00586dc8[4];
int igExtendByFunctionList_GetVTable(void) {
    Obj o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00527a90[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
