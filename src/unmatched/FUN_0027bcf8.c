int memset();
extern int DAT_004b5660[4];
extern int DAT_004b5668[4];
void FUN_0027bcf8(void) {
    int temp_v0;

    temp_v0 = DAT_004b5660[0] - 1;
    DAT_004b5660[0] = temp_v0;
    if (temp_v0 == 0) {
        memset(&DAT_004b5668[0], 0, 0x4000);
    }
}
