/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igObject_InitHeader(int *);
extern int DAT_00537220[4];
extern int *DAT_00586dc8[4];
int beModelCtrlDataList_GetVTable(void);
}
int beModelCtrlDataList_GetVTable(void) {
    int tmp[8];
    int off;

    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_00537220[0];
    off = *(int *)((char *)(DAT_00586dc8[0]) + 916);
    return *(int *)((char *)tmp + off);
}
