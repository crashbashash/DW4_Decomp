int sceMpegInit();
int FUN_0028b460();
extern int DAT_004beb10[4];
extern int DAT_00585630[4];
void FUN_002a96f0(void) {
    if (DAT_004beb10[0] != 0) {
        sceMpegInit();
        FUN_0028b460(&DAT_00585630[0], 0, 0x48);
    }
}
