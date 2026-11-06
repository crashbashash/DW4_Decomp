int FUN_0012a1e8();
int FUN_00273be8();
int igStrCmp();
int strcpy();
int strlen();
extern int DAT_004ab450[4];
extern char DAT_004f03d0[4];
extern char DAT_004f03d8[4];
void FUN_002745c0(char *arg0, int arg1) {
    char temp_v1;

    strcpy(arg1, &DAT_004ab450[0]);
    temp_v1 = *arg0;
    if ((temp_v1 != 0x2F) && (temp_v1 != 0x5C)) {
        FUN_0012a1e8(arg1, &DAT_004f03d0[0]);
    }
    FUN_0012a1e8(arg1, arg0);
    if (igStrCmp((arg1 + strlen(arg1)) - 2, &DAT_004f03d8[0]) != 0) {
        FUN_0012a1e8(arg1, &DAT_004f03d8[0]);
    }
    FUN_00273be8(arg1);
}
