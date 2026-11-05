/* 0x0019f560 - igGraphPathList_GetVTable. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
int igObject_InitHeader();
extern int DAT_0052a870[4];
extern int *DAT_00586dc8[4];
int igGraphPathList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_0052a870[0];
    off = *(int *)((char *)(DAT_00586dc8[0]) + 916);
    return *(int *)((char *)tmp + off);
}
