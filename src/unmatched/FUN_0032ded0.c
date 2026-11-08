int strncasecmp();
extern int DAT_004ffd40[4];
extern int DAT_00587368[4];
extern char GPR_00554de0;

void FUN_0032ded0(int arg0) {
    if (strncasecmp(arg0, &DAT_004ffd40[0], 5) == 0) {
        GPR_00554de0 = 1;
    } else {
        GPR_00554de0 = 0;
    }
    DAT_00587368[0] = arg0;
}
