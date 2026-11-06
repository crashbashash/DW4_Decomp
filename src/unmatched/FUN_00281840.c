int FUN_00281a00();
extern int DAT_00570c00[4];
void FUN_00281840(unsigned char *arg0, unsigned char *arg1) {
    FUN_00281a00(0xFC00, 0, 0, 8);
    *arg0 = *(int *)((char *)&(DAT_00570c00[0]) + 0);
    *arg1 = *(int *)((char *)&(DAT_00570c00[0]) + 4);
}
