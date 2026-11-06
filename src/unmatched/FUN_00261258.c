extern char DAT_0049a758[];
int FUN_00261218();
int FUN_00262118();
int FUN_00262678();
extern int DAT_0049a75c[4];
void FUN_00261258(void) {
    int temp_a0;

    temp_a0 = *(int *)DAT_0049a758;
    if ((temp_a0 != 0) && (DAT_0049a75c[0] >= 0)) {
        if (FUN_00262678(temp_a0) != 1) {
            FUN_00262118(*(int *)DAT_0049a758);
        }
        FUN_00261218();
    }
}
