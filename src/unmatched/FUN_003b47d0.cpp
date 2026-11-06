extern "C" {
int FUN_003b48a0();
extern void * DAT_0058aba0[4];
void *FUN_003b47d0(void);
}
void *FUN_003b47d0(void) {
    unsigned char b;
    if (DAT_0058aba0[0] != 0) {
        b = (*(int *)((char *)(DAT_0058aba0[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003b48a0();
done:
    return DAT_0058aba0[0];
}
