extern "C" {
int FUN_0033e350();
extern void * DAT_005878e0[4];
void *FUN_0033c900(void) {
    unsigned char b;
    if (DAT_005878e0[0] != 0) {
        b = (*(int *)((char *)(DAT_005878e0[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0033e350();
done:
    return DAT_005878e0[0];
}
}
