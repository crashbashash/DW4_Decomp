extern "C" {
/* FUN_00340af0 (0x00340af0): lazily creates the singleton when it is missing or its ready flag
 * (bit 2 of the word at +36) is clear, then returns it. Needs the pinned alternate compiler with
 * -O3,p: its branch-target alignment gives the extra nop of the retail body. */
int FUN_00340bb0();
extern void * DAT_00587be0[4];
void *FUN_00340af0(void) {
    unsigned char b;
    if (DAT_00587be0[0] != 0) {
        b = (*(int *)((char *)(DAT_00587be0[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00340bb0();
done:
    return DAT_00587be0[0];
}
}
