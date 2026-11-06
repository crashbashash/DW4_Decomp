int igObject_InitHeader();
extern int DAT_005277e0[4];
extern int *DAT_00586dc8[4];
int igAABox_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_005277e0[0];
    off = *(int *)((char *)(DAT_00586dc8[0]) + 916);
    return *(int *)((char *)tmp + off);
}
