int FUN_002607e8();
int FUN_002773d0();
extern int DAT_004ee240[4];
int FUN_00263b08(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004ee240[0]);
        return -1;
    }
    return FUN_002773d0(*(int *)((char *)(arg0) + 148));
}
