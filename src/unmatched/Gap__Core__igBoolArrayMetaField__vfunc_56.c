int FUN_00129ef8();
int FUN_0012a918();
extern int DAT_004f9588[4];
extern int DAT_004f9590[4];
extern int DAT_004f9598[4];
int Gap__Core__igBoolArrayMetaField__vfunc_56(void *arg0, char *arg1, int arg2) {
    int sp3C;
    int sp38;

    sp3C = 0;
    sp38 = 0;
    FUN_00129ef8(arg2, &DAT_004f9588[0], &sp38, &sp3C);
    if (sp3C > 0) {
        *arg1 = sp38 != 0;
        return sp3C;
    }
    if (FUN_0012a918(&DAT_004f9590[0], arg2, 4) == 0) {
        *arg1 = 1;
        return 4;
    }
    if (FUN_0012a918(&DAT_004f9598[0], arg2, 5) == 0) {
        *arg1 = 0;
        return 5;
    }
    return 0;
}
