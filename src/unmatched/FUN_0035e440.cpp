/* FUN_0035e440 (0x0035e440): lazily creates the singleton when it is missing or its ready flag
 * (bit 2 of the word at +36) is clear, then returns it. Needs the pinned alternate compiler with
 * -O3,p: its branch-target alignment gives the extra nop of the retail body. */
extern "C" {
int FUN_0035e520();
extern void * DAT_005893e8[4];
void *FUN_0035e440(void);
}

void *FUN_0035e440(void) {
    unsigned char b;
    if (DAT_005893e8[0] != 0) {
        b = (*(int *)((char *)(DAT_005893e8[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0035e520();
done:
    return DAT_005893e8[0];
}
