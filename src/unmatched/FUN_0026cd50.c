int FUN_002607e8();
extern int DAT_004eea98[4];
int FUN_0026cd50(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004eea98[0]);
        return -1;
    }
    return *(int *)((char *)(arg0) + 76);
}
