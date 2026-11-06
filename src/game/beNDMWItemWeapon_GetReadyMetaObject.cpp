/* beNDMWItemWeapon_GetReadyMetaObject (0x003c8cd0): lazily creates the singleton when it is
 * missing or its ready flag (bit 2 of the word at +36) is clear, then returns it. Needs the pinned
 * alternate compiler with -O3,p: its branch-target alignment gives the extra nop of the retail
 * body. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_003c8d60();
extern void * DAT_0058bf60[4];
void *beNDMWItemWeapon_GetReadyMetaObject(void) {
    unsigned char b;
    if (DAT_0058bf60[0] != 0) {
        b = (*(int *)((char *)(DAT_0058bf60[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003c8d60();
done:
    return DAT_0058bf60[0];
}
} /* extern "C" */
