extern "C" {
int FUN_003bb040();
extern void * DAT_0058af98[4];
void *FUN_003baf50(void);
}
void *FUN_003baf50(void) {
    unsigned char b;
    if (DAT_0058af98[0] != 0) {
        b = (*(int *)((char *)(DAT_0058af98[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003bb040();
done:
    return DAT_0058af98[0];
}
