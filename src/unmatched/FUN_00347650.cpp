extern "C" {
int FUN_003476e0();
extern void * DAT_00588070[4];
void *FUN_00347650(void) {
    unsigned char b;
    if (DAT_00588070[0] != 0) {
        b = (*(int *)((char *)(DAT_00588070[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003476e0();
done:
    return DAT_00588070[0];
}
}
