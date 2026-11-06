int igObject_InitHeader();
extern int DAT_00527d90[4];
extern int *DAT_00586dc8[4];
int igEmptyFunctionList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_00527d90[0];
    off = *(int *)((char *)(DAT_00586dc8[0]) + 916);
    return *(int *)((char *)tmp + off);
}
