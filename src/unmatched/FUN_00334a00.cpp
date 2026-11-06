extern "C" {
int FUN_00334a90();
extern void * DAT_00587650[4];
void *FUN_00334a00(void) {
    unsigned char b;
    if (DAT_00587650[0] != 0) {
        b = (*(int *)((char *)(DAT_00587650[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00334a90();
done:
    return DAT_00587650[0];
}
}
