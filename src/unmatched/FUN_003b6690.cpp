/* FUN_003b6690 (0x003b6690): lazily creates the singleton when it is missing or its ready flag
 * (bit 2 of the word at +36) is clear, then returns it. Needs the pinned alternate compiler with
 * -O3,p: its branch-target alignment gives the extra nop of the retail body. */
extern "C" {
int FUN_003b67e0();
extern void * DAT_0058aca8[4];
void *FUN_003b6690(void);
}
void *FUN_003b6690(void) {
    unsigned char b;
    if (DAT_0058aca8[0] != 0) {
        b = (*(int *)((char *)(DAT_0058aca8[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003b67e0();
done:
    return DAT_0058aca8[0];
}
