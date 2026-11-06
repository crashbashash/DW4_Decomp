extern char DAT_004b9698[];
int memset();
extern int DAT_004b96a0[4];
void FUN_0027c7c0(void) {
    if (*(int *)DAT_004b9698 == 0) {
        memset(&DAT_004b96a0[0], 0, 0xC00);
    }
    *(int *)DAT_004b9698 += 1;
}
