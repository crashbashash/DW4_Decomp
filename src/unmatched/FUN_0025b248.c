extern char DAT_00498730[];
int memset();
extern int DAT_00498738[4];
void FUN_0025b248(void) {
    if (*(int *)DAT_00498730 == 0) {
        memset(&DAT_00498738[0], 0, 0x300);
    }
    *(int *)DAT_00498730 += 1;
}
