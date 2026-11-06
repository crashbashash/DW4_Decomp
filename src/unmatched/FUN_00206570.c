int FUN_0020d270();
extern unsigned long long DAT_00491680[4];
extern int DAT_0056bf60[4];
extern long long DAT_0056bfe0[4];
extern long long DAT_0056bfe8[4];
extern long long DAT_0056bff0[4];
extern unsigned long long DAT_0056bff8[4];
void FUN_00206570(void) {
    long long sp18;
    unsigned long long temp_a2;

    DAT_0056bf60[0] = 1;
    FUN_0020d270(&sp18);
    temp_a2 = sp18 - DAT_0056bfe0[0];
    DAT_0056bff0[0] += temp_a2;
    DAT_0056bfe8[0] += 1;
    if (temp_a2 < (unsigned long long) DAT_00491680[0]) {
        DAT_00491680[0] = temp_a2;
    }
    if ((unsigned long long) DAT_0056bff8[0] < temp_a2) {
        DAT_0056bff8[0] = temp_a2;
    }
}
