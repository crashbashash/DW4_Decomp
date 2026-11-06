extern "C" {
int FUN_00340bb0();
extern void * DAT_00587be0[4];
void *FUN_00340af0(void) {
    unsigned char b;
    if (DAT_00587be0[0] != 0) {
        b = (*(int *)((char *)(DAT_00587be0[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00340bb0();
done:
    return DAT_00587be0[0];
}
}
