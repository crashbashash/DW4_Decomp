int igObject_InitHeader();
extern int DAT_00527100[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[32]; };
int igVertexDataList_GetVTable(void) {
    union U u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00527100[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}
