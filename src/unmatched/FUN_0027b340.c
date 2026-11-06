extern char DAT_004b5178[];
int memset();
extern int DAT_004b5180[4];
void FUN_0027b340(void) {
    if (*(int *)DAT_004b5178 == 0) {
        memset(&DAT_004b5180[0], 0, 0x480);
    }
    *(int *)DAT_004b5178 += 1;
}
