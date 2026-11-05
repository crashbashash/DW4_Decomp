int FUN_002607e8();
extern int DAT_004ede68[4];
int FUN_00262510(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004ede68[0]);
        return -3;
    }
    return *(int *)((char *)(arg0) + 20);
}
