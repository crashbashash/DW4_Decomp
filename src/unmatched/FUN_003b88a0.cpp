extern "C" {
int FUN_003b8a00();
extern void * DAT_0058ae08[4];
void *FUN_003b88a0(void);
}
void *FUN_003b88a0(void) {
    unsigned char b;
    if (DAT_0058ae08[0] != 0) {
        b = (*(int *)((char *)(DAT_0058ae08[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003b8a00();
done:
    return DAT_0058ae08[0];
}
