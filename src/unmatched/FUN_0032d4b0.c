int FUN_0012a918();
int strncpy();
int FUN_002ee430();
int FUN_0032ded0();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int DAT_004ffd28[4];
extern int DAT_00587330[4];
extern int DAT_00587358[4];
void FUN_0032d4b0(int *arg0, char *arg1) {
    int temp_s1;
    int var_v1;
    char *var_a0;

    if ((arg1 != 0) && (FUN_0012a918(arg1, &DAT_004ffd28[0], 7) == 0)) {
        var_a0 = arg1 + 7;
        do {
            var_a0 += 1;
        } while (*var_a0 != 0x2C);
        temp_s1 = (var_a0 - arg1) + 1;
        DAT_00587358[0] = FUN_002ee430(temp_s1 + 1);
        strncpy(DAT_00587358[0], arg1, temp_s1);
        *(char *)(DAT_00587358[0] + temp_s1) = 0;
        DAT_00587330[0] = DAT_00587358[0];
        FUN_0032ded0(DAT_00587358[0]);
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb418[0];
    }
}

