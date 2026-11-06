extern "C" {
int FUN_003b2a90();
extern void * DAT_0058ab10[4];
void *FUN_003b2930(void);
}
void *FUN_003b2930(void) {
    unsigned char b;
    if (DAT_0058ab10[0] != 0) {
        b = (*(int *)((char *)(DAT_0058ab10[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003b2a90();
done:
    return DAT_0058ab10[0];
}
