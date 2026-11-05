/* 0x002c2450 - igLibraryList_GetVTable. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
int igObject_InitHeader();
extern int DAT_00532830[4];
extern int *DAT_00586dc8[4];
int igLibraryList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_00532830[0];
    off = *(int *)((char *)(DAT_00586dc8[0]) + 916);
    return *(int *)((char *)tmp + off);
}
