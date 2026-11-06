int FUN_00458ec0();
extern void * DAT_0058c708[4];
void *igStatisticsItem_GetMetaObject(void) {
    unsigned char b;
    if (DAT_0058c708[0] != 0) {
        b = (*(int *)((char *)(DAT_0058c708[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00458ec0();
done:
    return DAT_0058c708[0];
}
