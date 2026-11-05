int FUN_002607e8();
extern int DAT_004eebc0[4];
char FUN_0026cf70(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004eebc0[0]);
        return 0;
    }
    return *(int *)((char *)(arg0) + 114);
}
