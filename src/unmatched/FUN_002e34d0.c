char *FUN_0012a314(char *s, int c);
unsigned int strlen(char *s);
char *strcpy(char *d, char *s);
char *strncpy(char *d, char *s, unsigned int n);
char *FUN_0012a1e8(char *d, char *s);
int igStrCmp(char *a, char *b);
extern char DAT_004f9468[];
extern char DAT_004f9a48[];

int FUN_002e34d0(char **arg0, char *arg1, int arg2) {
    char *temp_s1;
    char *temp_v0;
    char temp_v1;
    unsigned int var_s0;

    temp_s1 = *arg0;
    *arg1 = 0;
    if ((temp_s1 == 0) || (*temp_s1 == 0)) {
        return 0;
    }
    temp_v0 = FUN_0012a314(temp_s1, 0x2C);
    if (temp_v0 == 0) {
        var_s0 = strlen(temp_s1);
        if ((unsigned int) (arg2 - 2) <= var_s0) {
            return 0;
        }
        strcpy(arg1, temp_s1);
        *arg0 = 0;
    } else {
        var_s0 = temp_v0 - temp_s1;
        if ((unsigned int) (arg2 - 2) <= var_s0) {
            return 0;
        }
        strncpy(arg1, temp_s1, var_s0);
        arg1[var_s0] = 0;
        *arg0 = temp_v0 + 1;
    }
    if (igStrCmp(arg1, DAT_004f9468) == 0) {
        *arg1 = 0;
    } else {
        temp_v1 = arg1[var_s0 - 1];
        if (temp_v1 != 0x2F) {
            if (temp_v1 != 0x5C) {
                FUN_0012a1e8(arg1, DAT_004f9a48);
            }
        }
    }
    return 1;
}
