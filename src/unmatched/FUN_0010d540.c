extern int DAT_00555fe4[4];
extern int DAT_00555fec[4];
void FUN_0010d540(int arg0) {
    if (arg0 < 0) {
        *(int *)(((arg0 & 0x7FFFFFFF) * 0xC) + DAT_00555fe4[0]) = 0;
        return;
    }
    *(int *)((arg0 * 0xC) + DAT_00555fec[0]) = 0;
}
