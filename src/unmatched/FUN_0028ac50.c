extern int DAT_00573eb8[];
void FUN_0028ac50(void) {
    int i;
    int n = DAT_00573eb8[16];
    int *p = (int *)DAT_00573eb8[17];
    for (i = 0; i < n; i++) {
        *p = 1;
        p += 0x680 / 4;
    }
}
