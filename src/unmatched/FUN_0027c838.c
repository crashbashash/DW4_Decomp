int memset();
extern int DAT_004b9698[4];
extern int DAT_004b96a0[4];
void FUN_0027c838(void) {
    int temp_v0;

    temp_v0 = DAT_004b9698[0] - 1;
    DAT_004b9698[0] = temp_v0;
    if (temp_v0 == 0) {
        memset(&DAT_004b96a0[0], 0, 0xC00);
    }
}
