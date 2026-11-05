int FUN_002607e8();
extern int DAT_004eea38[4];
short FUN_0026cce0(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004eea38[0]);
        return -1;
    }
    return *(int *)((char *)(arg0) + 96);
}
