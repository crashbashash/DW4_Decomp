int igObject_InitHeader();
extern int DAT_0052b760[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[32]; };
int igNonRefCountedTransformList_GetVTable(void) {
    union U u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052b760[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}
