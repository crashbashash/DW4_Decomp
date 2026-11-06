typedef struct { int *vt; int pad[7]; } Obj;
int igObject_InitHeader();
extern int DAT_00531dc0[4];
extern void * DAT_00586dc8[4];
int igUnsignedCharList_GetVTable(void) {
    Obj o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00531dc0[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
