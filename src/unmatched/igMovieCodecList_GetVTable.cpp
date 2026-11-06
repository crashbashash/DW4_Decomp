extern "C" {
int igObject_InitHeader(int *);
extern int DAT_00533a60[4];
extern int *DAT_00586dc8[4];
int igMovieCodecList_GetVTable(void);
}
int igMovieCodecList_GetVTable(void) {
    int tmp[8];
    int off;

    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_00533a60[0];
    off = *(int *)((char *)(DAT_00586dc8[0]) + 916);
    return *(int *)((char *)tmp + off);
}
