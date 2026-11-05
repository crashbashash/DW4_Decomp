/* igStatisticsItem_GetMetaObject (0x00458ca0): lazily creates the singleton when it is missing or its
 * ready flag (bit 2 of the word at +36) is clear, then returns it.  Needs the
 * pinned alternate compiler with -O3,p (config/SLUS-20836/unit-compilers.tsv): its
 * branch-target alignment gives the extra nop of the retail body. */
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
