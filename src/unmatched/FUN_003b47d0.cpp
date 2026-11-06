/* FUN_003b47d0 (0x003b47d0): lazily creates the singleton when it is missing or its ready flag
 * (bit 2 of the word at +36) is clear, then returns it. Needs the pinned alternate compiler with
 * -O3,p: its branch-target alignment gives the extra nop of the retail body. */
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
