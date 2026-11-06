typedef struct { int *vt; int pad[7]; } Obj;
int igObject_InitHeader();
extern int DAT_00527170[4];
extern void * DAT_00586dc8[4];
int igVisualContextList_GetVTable(void) {
    Obj o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00527170[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
