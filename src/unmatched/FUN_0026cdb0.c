int FUN_002607e8();
extern int DAT_004eeaf8[4];
int FUN_0026cdb0(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004eeaf8[0]);
        return 0;
    }
    return *(int *)((char *)(arg0) + 20);
}
