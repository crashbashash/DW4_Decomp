int FUN_002607e8();
extern int DAT_004eeb60[4];
char FUN_0026ce10(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004eeb60[0]);
        return -1;
    }
    return *(int *)((char *)(arg0) + 113);
}
